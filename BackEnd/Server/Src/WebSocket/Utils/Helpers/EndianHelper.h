
#ifndef ENDIAN_HELPER_H
#define ENDIAN_HELPER_H

#include <cstdint>

#if defined(__APPLE__)
#include <libkern/OSByteOrder.h>
#define be64toh(x) OSSwapBigToHostInt64(x)
#elif defined(__linux__)
#include <endian.h>
#else
#error "Unsupported platform"
#endif

#endif // ENDIAN_HELPER_H