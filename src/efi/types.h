#include <stdint.h>
#pragma once

#if EFI_WORD_SIZE == 32
typedef int32_t INTN;
#elif EFI_WORD_SIZE == 64
typedef int64_t INTN;
#elif EFI_WORD_SIZE == 128
typedef INT128 INTN;
#else
typedef int64_t INTN;
#endif
#if EFI_WORD_SIZE == 32
typedef uint32_t UINTN;
#elif EFI_WORD_SIZE == 64
typedef uint64_t UINTN;
#elif EFI_WORD_SIZE == 128
typedef INT128 UINTN;
#else
typedef uint64_t UINTN;
#endif

typedef void VOID;
typedef VOID* EFI_EVENT;
typedef VOID* EFI_HANDLE;
typedef uint64_t EFI_LBA;
typedef uint64_t EFI_PHYSICAL_ADDRESS;
typedef uint64_t EFI_STATUS;
typedef uint64_t EFI_TL;
typedef uint64_t EFI_TPL;
typedef uint64_t EFI_VIRTUAL_ADDRESS;

typedef struct EFI_GUID {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
} EFI_GUID;

typedef struct EFI_TIME {
    uint16_t Year;
    uint8_t Month;
    uint8_t Day;
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
    uint8_t Pad1;
    uint32_t Nanosecond;
    int16_t TimeZone;
    uint8_t Daylight;
    uint8_t PAD2;
} EFI_TIME;

typedef struct EFI_TIME_CAPABILITIES {
    uint32_t Resolution;
    uint32_t Accuracy;
    bool SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef uint32_t EFI_IPv4_ADDRESS;
typedef uint8_t EFI_IPv6_ADDRESS[16];
typedef union {
    uint32_t Addr[4];
    EFI_IPv4_ADDRESS v4;
    EFI_IPv6_ADDRESS v6;
} EFI_IP_ADDRESS;
typedef uint8_t EFI_MAC_ADDRESS[32];