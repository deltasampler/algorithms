#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef _WIN32
    #include <BaseTsd.h>

    #ifndef ssize_t
        typedef SSIZE_T ssize_t;
    #endif
#else
    #include <unistd.h>
#endif

typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;

typedef ssize_t ssize;
typedef size_t usize;

typedef float f32;
typedef double f64;
