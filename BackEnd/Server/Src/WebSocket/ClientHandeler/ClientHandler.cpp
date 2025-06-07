//
// Created by ziga zoric on 07.06.25.
//

#include "ClientHandler.h"

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

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

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // no newlines
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


