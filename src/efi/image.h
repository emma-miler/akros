/**
 * @file efi-lip.h
 * @author Warren Mann (warren@nonvol.io)
 * @brief UEFI Loaded Image Protocol
 * @version 0.2.0
 * @date 2024-04-04
 * @copyright Copyright (c) 2024
 */

#ifndef _EFI_LIP_H
#define _EFI_LIP_H

#include "../efi.h"
#include "devicepath.h"

#define EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID                                     \
    {                                                                                  \
        0xbc62157e, 0x3e33, 0x4fec, { 0x99, 0x20, 0x2d, 0x3b, 0x36, 0xd7, 0x50, 0xdf } \
    }

#define EFI_LOADED_IMAGE_PROTOCOL_GUID                                                 \
    {                                                                                  \
        0x5b1b31a1, 0x9562, 0x11d2, { 0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }
#define EFI_LOADED_IMAGE_PROTOCOL_REVISION 0x1000

typedef EFI_STATUS(EFIAPI* EFI_IMAGE_UNLOAD)(IN EFI_HANDLE ImageHandle);
typedef struct EFI_LOADED_IMAGE_PROTOCOL {
    uint32_t Revision;
    EFI_HANDLE ParentHandle;
    EFI_SYSTEM_TABLE* SystemTable;
    EFI_HANDLE DeviceHandle;
    EFI_DEVICE_PATH_PROTOCOL* FilePath;
    VOID* Reserved;
    uint32_t LoadOptionsSize;
    VOID* LoadOptions;
    VOID* ImageBase;
    uint64_t ImageSize;
    EFI_MEMORY_TYPE ImageCodeType;
    EFI_MEMORY_TYPE ImageDataType;
    EFI_IMAGE_UNLOAD UnLoad;
} EFI_LOADED_IMAGE_PROTOCOL;

#endif // _EFI_LIP_H