/**
 * @file efi-dpp.h
 * @author Warren Mann (warren@nonvol.io)
 * @brief UEFI Device Path Protocol.
 * @version 0.2.0
 * @date 2024-04-04
 * @copyright Copyright (c) 2024
 */

#ifndef _EFI_DPP_H
#define _EFI_DPP_H

#include "types.h"

#define EFI_DEVICE_PATH_PROTOCOL_GUID                                                  \
    {                                                                                  \
        0x09576e91, 0x6d3f, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }

#define EFI_HARDWARE_DEVICE_PATH_TYPE                0x01
#define EFI_ACPI_DEVICE_PATH_TYPE                    0x02
#define EFI_MESSAGING_DEVICE_PATH_TYPE               0x03
#define EFI_MEDIA_DEVICE_PATH_TYPE                   0x04
#define EFI_BIOS_BOOT_SPECIFICATION_DEVICE_PATH_TYPE 0x05
#define EFI_END_OF_HARDWARE_DEVICE_PATH_TYPE         0x7f

#define EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE   0xff
#define EFI_END_INSTANCE_DEVICE_PATH_SUBTYPE 0x01

#define EFI_DEVICE_PATH_SUBTYPE_PCI        0x01
#define EFI_DEVICE_PATH_SUBTYPE_PCCARD     0x02
#define EFI_DEVICE_PATH_SUBTYPE_MEMMAP     0x03
#define EFI_DEVICE_PATH_SUBTYPE_VENDOR     0x04
#define EFI_DEVICE_PATH_SUBTYPE_CONTROLLER 0x05
#define EFI_DEVICE_PATH_SUBTYPE_BMC        0x06

#define EFI_DEVICE_PATH_SUBTYPE_ACPI          0x01
#define EFI_DEVICE_PATH_SUBTYPE_EXPANDED_ACPI 0x02
#define EFI_DEVICE_PATH_SUBTYPE_ADR           0x03
#define EFI_DEVICE_PATH_SUBTYPE_NVDIMM        0x04

#define EFI_DEVICE_PATH_SUBTYPE_ATAPI                        0x01
#define EFI_DEVICE_PATH_SUBTYPE_SCSI                         0x02
#define EFI_DEVICE_PATH_SUBTYPE_FIBRECHANNEL                 0x03
#define EFI_DEVICE_PATH_SUBTYPE_FIBRECHANNEL_EX              0x15
#define EFI_DEVICE_PATH_SUBTYPE_1394                         0x04
#define EFI_DEVICE_PATH_SUBTYPE_USB                          0x05
#define EFI_DEVICE_PATH_SUBTYPE_SATA                         0x12
#define EFI_DEVICE_PATH_SUBTYPE_USB_WWID                     0x13
#define EFI_DEVICE_PATH_SUBTYPE_DEVICE_LOGICAL_UNIT          0x14
#define EFI_DEVICE_PATH_SUBTYPE_USB_CLASS                    0x0f
#define EFI_DEVICE_PATH_SUBTYPE_I2O                          0x06
#define EFI_DEVICE_PATH_SUBTYPE_MAC_ADDRESS                  0x0b
#define EFI_DEVICE_PATH_SUBTYPE_IPv4                         0x0c
#define EFI_DEVICE_PATH_SUBTYPE_IPv6                         0x0d
#define EFI_DEVICE_PATH_SUBTYPE_VLAN                         0x14
#define EFI_DEVICE_PATH_SUBTYPE_INFINIBAND                   0x09
#define EFI_DEVICE_PATH_SUBTYPE_UART                         0x0e
#define EFI_DEVICE_PATH_SUBTYPE_VENDOR_DEFINED_MESSAGING     0x0a
#define EFI_DEVICE_PATH_SUBTYPE_UART_FLOW_CONTROL            0x10
#define EFI_DEVICE_PATH_SUBTYPE_SAS                          0x0a
#define EFI_DEVICE_PATH_SUBTYPE_SAS_EX                       0x16
#define EFI_DEVICE_PATH_SUBTYPE_ISCSI                        0x13
#define EFI_DEVICE_PATH_SUBTYPE_NVM_EXPRESS_NAMESPACE        0x17
#define EFI_DEVICE_PATH_SUBTYPE_URI                          0x18
#define EFI_DEVICE_PATH_SUBTYPE_UFS                          0x19
#define EFI_DEVICE_PATH_SUBTYPE_SD                           0x1a
#define EFI_DEVICE_PATH_SUBTYPE_BLUETOOTH                    0x1b
#define EFI_DEVICE_PATH_SUBTYPE_WIRELESS                     0x1c
#define EFI_DEVICE_PATH_SUBTYPE_EMMC                         0x1d
#define EFI_DEVICE_PATH_SUBTYPE_BLUETOOTH_LE                 0x1e
#define EFI_DEVICE_PATH_SUBTYPE_DNS                          0x1f
#define EFI_DEVICE_PATH_SUBTYPE_NVDIMM_NAMESPACE             0x20
#define EFI_DEVICE_PATH_SUBTYPE_REST_SERVICE                 0x21
#define EFI_DEVICE_PATH_SUBTYPE_VENDOR_SPECIFIC_REST_SERVICE 0x21
#define EFI_DEVICE_PATH_SUBTYPE_NVMEOF_NAMESPACE             0x22

#define EFI_DEVICE_PATH_SUBTYPE_HARD_DRIVE            0x01
#define EFI_DEVICE_PATH_SUBTYPE_CDROM                 0x02
#define EFI_DEVICE_PATH_SUBTYPE_VENDOR_DEFINED        0x03
#define EFI_DEVICE_PATH_SUBTYPE_FILE_PATH             0x04
#define EFI_DEVICE_PATH_SUBTYPE_MEDIA_PROTOCOL        0x05
#define EFI_DEVICE_PATH_SUBTYPE_PIWG_FW_FILE          0x06
#define EFI_DEVICE_PATH_SUBTYPE_PIWG_FW_VOLUME        0x07
#define EFI_DEVICE_PATH_SUBTYPE_RELATIVE_OFFSET_RANGE 0x08
#define EFI_DEVICE_PATH_SUBTYPE_RAM_DISK              0x09

#define EFI_DEVICE_PATH_SUBTYPE_BIOS_BOOT_SPECIFICATION 0x01

#define EFI_BIOS_BOOT_SPECIFICATION_DEVICE_TYPE_RESERVED         0x00
#define EFI_BIOS_BOOT_SPECIFICATION_DEVICE_TYPE_FLOPPY           0x01
#define EFI_BIOS_BOOT_SPECIFICATION_DEVICE_TYPE_HARD_DISK        0x02
#define EFI_BIOS_BOOT_SPECIFICATION_DEVICE_TYPE_CD_ROM           0x03
#define EFI_BIOS_BOOT_SPECIFICATION_DEVICE_TYPE_PCMCIA           0x04
#define EFI_BIOS_BOOT_SPECIFICATION_DEVICE_TYPE_USB              0x05
#define EFI_BIOS_BOOT_SPECIFICATION_DEVICE_TYPE_EMBEDDED_NETWORK 0x06
#define EFI_BIOS_BOOT_SPECIFICATION_DEVICE_TYPE_BEV_DEVICE       0x80
#define EFI_BIOS_BOOT_SPECIFICATION_DEVICE_TYPE_UNKNOWN          0xff

typedef struct EFI_DEVICE_PATH_PROTOCOL {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
} EFI_DEVICE_PATH_PROTOCOL;

typedef struct EFI_PCI_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t Function;
    uint8_t Device;
} EFI_PCI_DEVICE_PATH;

typedef struct EFI_PCCARD_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t FunctionNumber;
} EFI_PCCARD_DEVICE_PATH;

typedef struct EFI_MEMORY_MAPPED_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t MemoryType;
    uint64_t StartAddress;
    uint64_t EndAddress;
} EFI_MEMORY_MAPPED_DEVICE_PATH;

typedef struct EFI_VENDOR_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    EFI_GUID VendorGUID;
    uint8_t VendorDefinedData[];
} EFI_VENDOR_DEVICE_PATH;

typedef struct EFI_CONTROLLER_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t ControllerNumber;
} EFI_CONTROLLER_DEVICE_PATH;

typedef struct EFI_BMC_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t InterfaceType;
    uint64_t BaseAddress;
} EFI_BMC_DEVICE_PATH;

typedef struct EFI_ACPI_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t HID;
    uint32_t UID;
} EFI_ACPI_DEVICE_PATH;

typedef struct EFI_EXPANDED_ACPI_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t HID;
    uint32_t UID;
    uint32_t CID;
    uint8_t STR[];
} EFI_EXPANDED_ACPI_DEVICE_PATH;

typedef struct EFI_ADR_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t _ADR[];
} EFI_ADR_DEVICE_PATH;

typedef struct EFI_NVDIMM_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t NFITDeviceHandle;
} EFI_NVDIMM_DEVICE_PATH;

typedef struct EFI_ATAPI_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t PrimarySecondary;
    uint8_t SlaveMaster;
    uint16_t LUN;
} EFI_ATAPI_DEVICE_PATH;

typedef struct EFI_SCSI_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint16_t TargetId;
    uint16_t LUN;
} EFI_SCSI_DEVICE_PATH;

typedef struct EFI_FIBRECHANNEL_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t Reserved;
    uint64_t WorldWideName;
    uint64_t LUN;
} EFI_FIBRECHANNEL_DEVICE_PATH;

typedef struct EFI_FIBRECHANNEL_EX_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t Reserved;
    uint64_t WorldWideName;
    uint64_t LUN;
} EFI_FIBRECHANNEL_EX_DEVICE_PATH;

typedef struct EFI_1394_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t Reserved;
    uint64_t Guid;
} EFI_1394_DEVICE_PATH;

typedef struct EFI_USB_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t USBParentPortNumber;
    uint8_t Interface;
} EFI_USB_DEVICE_PATH;

typedef struct EFI_SATA_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint16_t HBAPortNumber;
    uint16_t PortMultiplierPortNumber;
    uint16_t LUN;
} EFI_SATA_DEVICE_PATH;

typedef struct EFI_USB_WWID_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint16_t InterfaceNumber;
    uint16_t VendorId;
    uint16_t DeviceProductId;
    uint8_t SerialNumber[];
} EFI_USB_WWID_DEVICE_PATH;

typedef struct EFI_DEVICE_LOGICAL_UNIT {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t LUN;
} EFI_DEVICE_LOGICAL_UNIT;

typedef struct EFI_USB_CLASS_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint16_t VendorId;
    uint16_t ProductId;
    uint8_t DeviceClass;
    uint8_t DeviceSubClass;
    uint8_t DeviceProtocol;
} EFI_USB_CLASS_DEVICE_PATH;

typedef struct EFI_I2O_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t TID;
} EFI_I2O_DEVICE_PATH;

typedef struct EFI_MAC_ADDRESS_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    EFI_MAC_ADDRESS MACAddress;
    uint8_t IfType;
} EFI_MAC_ADDRESS_DEVICE_PATH;

typedef struct EFI_IPV4_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    EFI_IPv4_ADDRESS LocalIpAddress;
    EFI_IPv4_ADDRESS RemoteIpAddress;
    uint16_t LocalPort;
    uint16_t RemotePort;
    uint16_t Protocol;
    bool StaticIpAddress;
    EFI_IPv4_ADDRESS GatewayIpAddress;
    EFI_IPv4_ADDRESS SubnetMask;
} EFI_IPV4_DEVICE_PATH;

typedef struct EFI_IPV6_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    EFI_IPv6_ADDRESS LocalIpAddress;
    EFI_IPv6_ADDRESS RemoteIpAddress;
    uint16_t LocalPort;
    uint16_t RemotePort;
    uint16_t Protocol;
    bool IPAddressOrigin;
    uint8_t PrefixLength;
    EFI_IPv6_ADDRESS GatewayIPAddress;
} EFI_IPV6_DEVICE_PATH;

typedef struct EFI_VLAN_DEVICE_PATH_NODE {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint16_t Vlanid;
} EFI_VLAN_DEVICE_PATH_NODE;

typedef struct EFI_INFINIBAND_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t ResourceFlags;
    uint8_t PortGID[16];
    uint64_t ServiceId;
    uint64_t TargetPortId;
    uint64_t DeviceId;
} EFI_INFINIBAND_DEVICE_PATH;

typedef struct EFI_UART_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t Reserved;
    uint64_t BaudRate;
    uint8_t DataBits;
    uint8_t Parity;
    uint8_t StopBits;
} EFI_UART_DEVICE_PATH;

typedef struct EFI_VENDOR_DEFINED_MESSAGING_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    EFI_GUID VendorGUID;
    uint8_t VendorDefinedData[];
} EFI_VENDOR_DEFINED_MESSAGING_DEVICE_PATH;

typedef struct EFI_UART_FLOW_CONTROL_MESSAGING_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    EFI_GUID VendorGUID;
    uint32_t FlowControlMap;
} EFI_UART_FLOW_CONTROL_MESSAGING_PATH;

typedef struct EFI_SAS_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    EFI_GUID VendorGUID;
    uint32_t Reserved;
    uint64_t SasAddress;
    uint64_t LUN;
    uint16_t DeviceTopologyInfo;
    uint16_t RelativeTargetPort;
} EFI_SAS_DEVICE_PATH;

typedef struct EFI_SAS_EXTENDED_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint64_t SasAddress;
    uint64_t LUN;
    uint16_t DeviceTopologyInfo;
    uint16_t RelativeTargetPort;
} EFI_SAS_EXTENDED_DEVICE_PATH;

typedef struct EFI_ISCSI_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint16_t Protocol;
    uint16_t Options;
    uint64_t LUN;
    uint16_t TargetPortalGroupTag;
    uint8_t iSCSITargetName[];
} EFI_ISCSI_DEVICE_PATH;

typedef struct EFI_NVM_EXPRESS_NAMESPACE_MESSAGING_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t NamespaceId;
    uint64_t IEEEExtendedUniqueIdentifier;
} EFI_NVM_EXPRESS_NAMESPACE_DEVICE_MESSAGING_PATH;

typedef struct EFI_URI_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t Uri[];
} EFI_URI_DEVICE_PATH;

typedef struct EFI_UFS_DEVICE_MESSAGING_DEVICE_PATH_NODE {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t TargetID;
    uint8_t LUN;
} EFI_UFS_DEVICE_MESSAGING_DEVICE_PATH_NODE;

typedef struct EFI_SD_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t SlotNumber;
} EFI_SD_DEVICE_PATH;

typedef struct EFI_BLUETOOTH_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t DeviceAddress[6];
} EFI_BLUETOOTH_DEVICE_PATH;

typedef struct EFI_WIRELESS_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t SSID[32];
} EFI_WIRELESS_DEVICE_PATH;

typedef struct EFI_EMMC_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t SlotNumber;
} EFI_EMMC_DEVICE_PATH;

typedef struct EFI_BLUETOOTH_LE_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t DeviceAddress[6];
    uint8_t AddressType;
} EFI_BLUETOOTH_LE_DEVICE_PATH;

typedef struct EFI_DNS_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    bool IsIPv6;
    EFI_IP_ADDRESS DNSServerAddress[];
} EFI_DNS_DEVICE_PATH;

typedef struct EFI_NVDIMM_NAMESPACE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    EFI_GUID Uuid;
} EFI_NVDIMM_NAMESPACE_PATH;

typedef struct EFI_REST_SERVICE_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t RESTService;
    uint8_t AccessMode;
} EFI_REST_SERVICE_DEVICE_PATH;

typedef struct EFI_VENDOR_SPECIFIC_REST_SERVICE_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t RESTService;
    uint8_t AccessMode;
    EFI_GUID VendorGUID;
    uint8_t VendorDefinedData[];
} EFI_VENDOR_SPECIFIC_REST_SERVICE_DEVICE_PATH;

typedef struct EFI_NVMEOF_NAMESPACE_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t NIDT;
    uint8_t NID[16];
    uint8_t SubsystemNQN[];
} EFI_NVMEOF_NAMESPACE_DEVICE_PATH;

typedef struct EFI_HARD_DRIVE_MEDIA_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t PartitionNumber;
    uint64_t PartitionStart;
    uint64_t PartitionSize;
    uint8_t Signature[16];
    uint8_t PartitionFormat;
    uint8_t SignatureType;
} EFI_HARD_DRIVE_MEDIA_DEVICE_PATH;

typedef struct EFI_CDROM_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t BootEntry;
    uint64_t PartitionStart;
    uint64_t PartitionSize;
} EFI_CDROM_DEVICE_PATH;

typedef struct EFI_VENDOR_DEFINED_MEDIA_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    EFI_GUID VendorGUID;
    uint8_t VendorDefinedData[];
} EFI_VENDOR_DEFINED_MEDIA_DEVICE_PATH;

typedef struct EFI_FILE_PATH_MEDIA_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t PathName[];
} EFI_FILE_PATH_MEDIA_DEVICE_PATH;

typedef struct EFI_MEDIA_PROTOCOL_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    EFI_GUID ProtocolGUID;
} EFI_MEDIA_PROTOCOL_DEVICE_PATH;

typedef struct EFI_PIWG_FW_FILE_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t Contents[];
} EFI_PIWG_FW_FILE_DEVICE_PATH;

typedef struct EFI_PIWG_FW_VOLUME_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint8_t Contents[];
} EFI_PIWG_FW_VOLUME_DEVICE_PATH;

typedef struct EFI_RELATIVE_OFFSET_RANGE_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint32_t Reserved;
    uint64_t StartingOffset;
    uint64_t EndingOffset;
} EFI_RELATIVE_OFFSET_RANGE_DEVICE_PATH;

typedef struct EFI_RAM_DISK_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint64_t StartingAddress;
    uint64_t EndingAddress;
    EFI_GUID DiskTypeGUID;
    uint16_t DiskInstance;
} EFI_RAM_DISK_DEVICE_PATH;

typedef struct EFI_BIOSBOOT_SPECIFICATION_DEVICE_PATH {
    uint8_t Type;
    uint8_t SubType;
    uint16_t Length;
    uint16_t DeviceType;
    uint16_t StatusFlag;
    uint8_t DescriptionString[];
} EFI_BIOSBOOT_SPECIFICATION_DEVICE_PATH;

#endif // _EFI_DPP_H