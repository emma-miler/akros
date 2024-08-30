/**
 * @file efi-rs.h
 * @author Warren Mann (warren@nonvol.io)
 * @brief UEFI Runtime Services.
 * @version 0.2.0
 * @date 2024-04-04
 * @copyright Copyright (c) 2024
 */

#ifndef _EFI_RS_H
#define _EFI_RS_H

#include "types.h"

#define EFI_OPTIONAL_POINTER 0x00000001

#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET  0x00010000
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE 0x00020000
#define CAPSULE_FLAGS_INITIATE_RESET        0x00040000

typedef enum EFI_RESET_TYPE { EfiResetCold, EfiResetWarm, EfiResetShutdown, EfiResetPlatformSpecific } EFI_RESET_TYPE;

typedef struct EFI_CAPSULE_BLOCK_DESCRIPTOR {
    uint64_t Length;
    union {
        EFI_PHYSICAL_ADDRESS DataBlock;
        EFI_PHYSICAL_ADDRESS ContinuationPointer;
    } Union;
} EFI_CAPSULE_BLOCK_DESCRIPTOR;

typedef struct EFI_CAPSULE_HEADER {
    EFI_GUID CapsuleGuid;
    uint32_t HeaderSize;
    uint32_t Flags;
    uint32_t CapsuleImageSize;
} EFI_CAPSULE_HEADER;

#include "../efi.h"

typedef EFI_STATUS(EFIAPI* EFI_GET_VARIABLE)(IN char16_t* VariableName, IN EFI_GUID* VendorGuid, OUT uint32_t* Attributes, IN OUT UINTN* DataSize, OUT VOID* Data);
typedef EFI_STATUS(EFIAPI* EFI_GET_NEXT_VARIABLE_NAME)(IN OUT UINTN* VariableNameSize, IN OUT char16_t* VariableName, IN OUT EFI_GUID* VendorGuid);
typedef EFI_STATUS(EFIAPI* EFI_SET_VARIABLE)(IN char16_t* VariableName, IN EFI_GUID* VendorGuid, IN uint32_t Attributes, IN UINTN DataSize, IN VOID* Data);
typedef EFI_STATUS(EFIAPI* EFI_QUERY_VARIABLE_INFO)(IN uint32_t Attributes, OUT uint64_t* MaximumVariableStorageSize, OUT uint64_t* RemainingVariableStorageSize, OUT uint64_t* MaximumVariableSize);
typedef EFI_STATUS(EFIAPI* EFI_GET_TIME)(OUT EFI_TIME* Time, OUT EFI_TIME_CAPABILITIES* Capabilities);
typedef EFI_STATUS(EFIAPI* EFI_SET_TIME)(IN EFI_TIME* Time);
typedef EFI_STATUS(EFIAPI* EFI_GET_WAKEUP_TIME)(OUT bool* Enabled, OUT bool* Pending, OUT EFI_TIME* Time);
typedef EFI_STATUS(EFIAPI* EFI_SET_WAKEUP_TIME)(IN bool Enable, IN EFI_TIME* Time);
typedef EFI_STATUS(EFIAPI* EFI_SET_VIRTUAL_ADDRESS_MAP)(IN UINTN MemoryMapSize, IN UINTN DescriptorSize, IN uint32_t DescriptorVersion, IN EFI_MEMORY_DESCRIPTOR* VirtualMap);
typedef EFI_STATUS(EFIAPI* EFI_CONVERT_POINTER)(IN UINTN DebugDisposition, IN VOID** Address);
typedef EFI_STATUS(EFIAPI* EFI_RESET_SYSTEM)(IN EFI_RESET_TYPE ResetType, IN EFI_STATUS ResetStatus, IN UINTN DataSize, IN VOID* ResetData);
typedef EFI_STATUS(EFIAPI* EFI_GET_NEXT_HIGH_MONO_COUNT)(OUT uint32_t* HighCount);
typedef EFI_STATUS(EFIAPI* EFI_UPDATE_CAPSULE)(IN EFI_CAPSULE_HEADER** CapsuleHeaderArray, IN UINTN CapsuleCount, IN EFI_PHYSICAL_ADDRESS ScatterGatherList);
typedef EFI_STATUS(EFIAPI* EFI_QUERY_CAPSULE_CAPABILITIES)(IN EFI_CAPSULE_HEADER** CapsuleHeaderArray, IN UINTN CapsuleCount, OUT uint64_t* MaximumCapsuleSize, OUT EFI_RESET_TYPE* ResetType);

#endif // _EFI_RS_H