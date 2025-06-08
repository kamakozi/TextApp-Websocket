//
// Created by ziga zoric on 07.06.25.
//

#include "ClientHandler.h"
#include "../Utils/Helpers/EndianHelper.h"

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <libkern/OSByteOrder.h>
#include <openssl/buffer.h>
#include <thread>

ClientHandler::ClientHandler(int clientSocket):clientSocket(clientSocket) {}

void ClientHandler::handle() {
    std::string request = readRequest();
    std::size_t keyPos = request.find("Sec-WebSocket-Key: ");
    if (keyPos == std::string::npos) {
        perror("WebSocket key not found!");
        close(clientSocket);
        return;
    }

    std::string clientKey = request.substr(keyPos + 19, request.find("\r\n", keyPos) - (keyPos + 19));
    std::string acceptKey = generateAcceptKey(clientKey);
    sendHandshakeResponse(acceptKey);


    while (true) {
        std::string received = readFrame();
        if (received.empty()) break;

        std::cout << "Client says: " << received << std::endl;
        sendFrame("Echo: " + received);
    }

    close(clientSocket);
}

std::string ClientHandler::readRequest() {
    char buffer[2048];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer)-1,0);
    if (bytesRead <= 0 ) {
        std::cerr << "Failed to read request" << std::endl;
        return  "";
    }

    buffer[bytesRead] = '\0';
    return std::string(buffer);
}

std::string ClientHandler::generateAcceptKey(const std::string& clientKey) {
    std::string GUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    std::string fullKey = clientKey + GUID;

    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(fullKey.c_str()), fullKey.size(), hash);

    BIO* bio = BIO_new(BIO_s_mem());
    BIO* b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, hash, SHA_DIGEST_LENGTH);
    BIO_flush(bio);

    BUF_MEM* bufferPtr;
    BIO_get_mem_ptr(bio, &bufferPtr);

    std::string acceptKey(bufferPtr->data, bufferPtr->length);
    BIO_free_all(bio);

    return acceptKey;
}

void ClientHandler::sendHandshakeResponse(const std::string& acceptKey) {
    std::ostringstream response;
    response << "HTTP/1.1 101 Switching Protocols\r\n"
             << "Upgrade: websocket\r\n"
             << "Connection: Upgrade\r\n"
             << "Sec-WebSocket-Accept: " << acceptKey << "\r\n\r\n";

    std::string resp = response.str();
    send(clientSocket, resp.c_str(), resp.size(), 0);
}

std::string ClientHandler::readFrame() {
    char header[2];
    ssize_t bytesRead = recv(clientSocket,header,2,0);
    if (bytesRead < 2) {
        std::cerr << "Failed to read frame header" << std::endl;
    }

    bool isMashed = header[1] & 0x80;
    uint64_t payloadLength =  header[1] & 0x7F;
    if (payloadLength == 126) {
        uint64_t extendedLength;
        recv(clientSocket,&extendedLength,2,0);
        payloadLength = ntohs(extendedLength);
    }else if (payloadLength == 127) {
        uint64_t extendedLength;
        recv(clientSocket,&extendedLength,8,0);
        payloadLength = be64toh(extendedLength);
    }

    char maskingKey[4];
    recv(clientSocket,maskingKey,4,0);

    std::vector<char> maskedPayload(payloadLength);
    recv(clientSocket,maskedPayload.data(),payloadLength,0);

    std::string decode;
    for (size_t i = 0; i < payloadLength;i++) {
        decode += maskedPayload[i] ^ maskingKey[i % 4];
    }
    return decode;

}

void ClientHandler::sendFrame(const std::string& message) {
    std::vector<char> frame;

    frame.push_back(0x81);

    size_t length = message.size();
    if (length <= 125) {
        frame.push_back(static_cast<char>(length));
    } else if (length <= 65535) {
        frame.push_back(126);
        frame.push_back((length >> 8) & 0xFF);
        frame.push_back(length & 0xFF);
    } else {
        frame.push_back(127);
        for (int i = 7; i >= 0; --i) {
            frame.push_back((length >> (8 * i)) & 0xFF);
        }
    }

    frame.insert(frame.end(), message.begin(), message.end());

    send(clientSocket, frame.data(), frame.size(), 0);
}


