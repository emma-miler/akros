/**
 * @file efi-pbcp.h
 * @author Mara Sophie Grosch (littlefox@lf-net.org)
 * @brief Pxe Base Code Protocol and Pxe Base Code Callback Protocol.
 * @version 0.2.0
 * @date 2024-04-04
 * @copyright Copyright (c) 2024
 */

#ifndef _EFI_PBCP_H
#define _EFI_PBCP_H

#include "../efi.h"

// first definitions for PXE_BASE_CODE_PROTOCOL constants
#define EFI_PXE_BASE_CODE_PROTOCOL_GUID                                                \
    {                                                                                  \
        0x03C4E603, 0xAC28, 0x11d3, { 0x9A, 0x2D, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D } \
    }

#define EFI_PXE_BASE_CODE_MAX_IPCNT          8
#define EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES    8
#define EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES  8
#define EFI_PXE_BASE_CODE_BOOT_LAYER_INITIAL 0

// now definitions for PXE_BASE_CODE_CALLBACK_PROTOCOL constants
#define EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_GUID                                       \
    {                                                                                  \
        0x245DCA21, 0xFB7B, 0x11d3, { 0x8F, 0x01, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B } \
    }
#define EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_REVISION 0x00010000

// types for the PXE_BASE_CODE_PROTOCOL
struct EFI_PXE_BASE_CODE_PROTOCOL;

typedef uint16_t EFI_PXE_BASE_CODE_UDP_PORT;

typedef struct {
    uint16_t Type;
    bool AcceptAnyResponse;
    uint8_t _reserved;
    EFI_IP_ADDRESS IpAddr;
} EFI_PXE_BASE_CODE_SRVLIST;

typedef struct {
    bool UseMCast;
    bool UseBCast;
    bool UseUCast;
    bool MustUseList;
    EFI_IP_ADDRESS ServerMCastIp;
    uint16_t IpCnt;
    EFI_PXE_BASE_CODE_SRVLIST SrvList[EFI_PXE_BASE_CODE_MAX_IPCNT];
} EFI_PXE_BASE_CODE_DISCOVER_INFO;

typedef struct {
    EFI_IP_ADDRESS MCastIp;
    EFI_PXE_BASE_CODE_UDP_PORT CPort;
    EFI_PXE_BASE_CODE_UDP_PORT SPort;
    uint16_t ListenTimeout;
    uint16_t TransmitTimeout;
} EFI_PXE_BASE_CODE_MTFTP_INFO;

typedef struct {
    uint8_t Filters;
    uint8_t IpCnt;
    uint16_t _reserved;
    EFI_IP_ADDRESS IpList[EFI_PXE_BASE_CODE_MAX_IPCNT];
} EFI_PXE_BASE_CODE_IP_FILTER;

typedef struct {
    EFI_IP_ADDRESS IpAddr;
    EFI_MAC_ADDRESS MacAddr;
} EFI_PXE_BASE_CODE_ARP_ENTRY;

typedef struct {
    EFI_IP_ADDRESS IpAddr;
    EFI_IP_ADDRESS SubnetMask;
    EFI_IP_ADDRESS GwAddr;
} EFI_PXE_BASE_CODE_ROUTE_ENTRY;

typedef struct {
    uint8_t BootpOpcode;
    uint8_t BootpHwType;
    uint8_t BootpHwAddrLen;
    uint8_t BootpGateHops;
    uint32_t BootpIdent;
    uint16_t BootpSeconds;
    uint16_t BootpFlags;
    uint8_t BootpCiAddr[4];
    uint8_t BootpYiAddr[4];
    uint8_t BootpSiAddr[4];
    uint8_t BootpGiAddr[4];
    uint8_t BootpHwAddr[16];
    uint8_t BootpSrvName[64];
    uint8_t BootpBootFile[128];
    uint32_t DhcpMagik;
    uint8_t DhcpOptions[56];
} EFI_PXE_BASE_CODE_DHCPV4_PACKET;

typedef struct {
    uint32_t MessageType : 8;
    uint32_t TransactionId : 24;
    uint8_t DhcpOptions[1024];
} EFI_PXE_BASE_CODE_DHCPV6_PACKET;

typedef union {
    uint8_t Raw[1472];
    EFI_PXE_BASE_CODE_DHCPV6_PACKET Dhcpv6;
    EFI_PXE_BASE_CODE_DHCPV4_PACKET Dhcpv4;
} EFI_PXE_BASE_CODE_PACKET;

typedef struct {
    uint8_t Type;
    uint8_t Code;
    uint16_t Checksum;
    union {
        uint32_t _reserved;
        uint32_t Mtu;
        uint32_t Pointer;
        struct {
            uint16_t Identifier;
            uint16_t Sequence;
        } Echo;
    } u;
    uint8_t Data[494];
} EFI_PXE_BASE_CODE_ICMP_ERROR;

typedef struct {
    uint8_t ErrorCode;
    uint8_t ErrorString[127];
} EFI_PXE_BASE_CODE_TFTP_ERROR;

typedef struct {
    bool Started;
    bool IPv6Available;
    bool IPv6Supported;
    bool UsingIPv6;
    bool BisSupported;
    bool BisDetected;
    bool AutoArp;
    bool SendGUID;
    bool DhcpDiscoverValid;
    bool DhcpAckReceived;
    bool ProxyOfferReceived;
    bool PxeDiscoverValid;
    bool PxeReplyReceived;
    bool PxeBisReplyReceived;
    bool IcmpErrorReceived;
    bool TftpErrorReceived;
    bool MakeCallbacks;
    uint8_t TTL;
    uint8_t ToS;
    EFI_IP_ADDRESS StationIp;
    EFI_IP_ADDRESS SubnetMask;
    EFI_PXE_BASE_CODE_PACKET DhcpDiscover;
    EFI_PXE_BASE_CODE_PACKET DhcpAck;
    EFI_PXE_BASE_CODE_PACKET ProxyOffer;
    EFI_PXE_BASE_CODE_PACKET PxeDiscover;
    EFI_PXE_BASE_CODE_PACKET PxeReply;
    EFI_PXE_BASE_CODE_PACKET PxeBisReply;
    EFI_PXE_BASE_CODE_IP_FILTER IpFilter;
    uint32_t ArpCacheEntries;
    EFI_PXE_BASE_CODE_ARP_ENTRY ArpCache[EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES];
    uint32_t RouteTableEntries;
    EFI_PXE_BASE_CODE_ROUTE_ENTRY
    RouteTable[EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES];
    EFI_PXE_BASE_CODE_ICMP_ERROR IcmpError;
    EFI_PXE_BASE_CODE_TFTP_ERROR TftpError;
} EFI_PXE_BASE_CODE_MODE;

typedef enum {
    EFI_PXE_BASE_CODE_TFTP_FIRST,
    EFI_PXE_BASE_CODE_TFTP_GET_FILE_SIZE,
    EFI_PXE_BASE_CODE_TFTP_READ_FILE,
    EFI_PXE_BASE_CODE_TFTP_WRITE_FILE,
    EFI_PXE_BASE_CODE_TFTP_READ_DIRECTORY,
    EFI_PXE_BASE_CODE_MTFTP_GET_FILE_SIZE,
    EFI_PXE_BASE_CODE_MTFTP_READ_FILE,
    EFI_PXE_BASE_CODE_MTFTP_READ_DIRECTORY,
    EFI_PXE_BASE_CODE_MTFTP_LAST
} EFI_PXE_BASE_CODE_TFTP_OPCODE;

typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_START)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This, IN bool UseIpv6);
typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_STOP)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This);
typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_DHCP)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This, IN bool SortOffers);
typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_DISCOVER)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This, IN uint16_t Type, IN uint16_t* Layer, IN bool UseBis, IN EFI_PXE_BASE_CODE_DISCOVER_INFO* Info);
typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_MTFTP)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This,
                                                    IN EFI_PXE_BASE_CODE_TFTP_OPCODE Operation,
                                                    IN OUT VOID* Buffer,
                                                    IN bool Overwrite,
                                                    IN OUT uint16_t* BufferSize,
                                                    IN UINTN* BlockSize,
                                                    IN EFI_IP_ADDRESS* ServerIp,
                                                    IN uint8_t* Filename,
                                                    IN EFI_PXE_BASE_CODE_MTFTP_INFO* Info,
                                                    IN bool DontUseBuffer);
typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_UDP_WRITE)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This,
                                                        IN uint16_t OpFlags,
                                                        IN EFI_IP_ADDRESS* DestIp,
                                                        IN EFI_PXE_BASE_CODE_UDP_PORT* DestPort,
                                                        IN EFI_IP_ADDRESS* GatewayIp,
                                                        IN EFI_IP_ADDRESS* SrcIp,
                                                        IN OUT EFI_PXE_BASE_CODE_UDP_PORT* SrcPort,
                                                        IN UINTN* HeaderSize,
                                                        IN VOID* HeaderPtr,
                                                        IN UINTN* BufferSize,
                                                        IN VOID* BufferPtr);
typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_UDP_READ)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This,
                                                       IN uint16_t OpFlags,
                                                       IN OUT EFI_IP_ADDRESS* DestIp,
                                                       IN OUT EFI_PXE_BASE_CODE_UDP_PORT* DestPort,
                                                       IN OUT EFI_IP_ADDRESS* SrcIp,
                                                       IN OUT EFI_PXE_BASE_CODE_UDP_PORT* SrcPort,
                                                       IN UINTN* HeaderSize,
                                                       IN VOID* HeaderPtr,
                                                       IN OUT UINTN* BufferSize,
                                                       IN VOID* BufferPtr);
typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_SET_IP_FILTER)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This, IN EFI_PXE_BASE_CODE_IP_FILTER* NewFilter);
typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_ARP)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This, IN EFI_IP_ADDRESS* IpAddr, IN EFI_MAC_ADDRESS* MacAddr);
typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_SET_PARAMETERS)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This, IN uint8_t* NewAutoArp, IN uint8_t* NewSendGUID, IN uint8_t* NewTTL, IN uint8_t* NewToS, IN uint8_t* NewMakeCallback);
typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_SET_STATION_IP)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This, IN EFI_IP_ADDRESS* NewStationIp, IN EFI_IP_ADDRESS* NewSubnetMask);
typedef EFI_STATUS(EFIAPI* EFI_PXE_BASE_CODE_SET_PACKETS)(IN struct EFI_PXE_BASE_CODE_PROTOCOL* This,
                                                          IN uint8_t* NewDhcpDiscoverValid,
                                                          IN uint8_t* NewDhcpAckReceived,
                                                          IN uint8_t* NewProxyOfferReceived,
                                                          IN uint8_t* NewPxeOfferValid,
                                                          IN uint8_t* NewPxeReplyReceived,
                                                          IN uint8_t* NewPxeBisReplyReceived,
                                                          IN EFI_PXE_BASE_CODE_PACKET* NewDhcpDiscover,
                                                          IN EFI_PXE_BASE_CODE_PACKET* NewDhcpAck,
                                                          IN EFI_PXE_BASE_CODE_PACKET* NewProxyOffer,
                                                          IN EFI_PXE_BASE_CODE_PACKET* NewPxeOffer,
                                                          IN EFI_PXE_BASE_CODE_PACKET* NewPxeReply,
                                                          IN EFI_PXE_BASE_CODE_PACKET* NewPxeBisReply);

typedef struct EFI_PXE_BASE_CODE_PROTOCOL {
    uint64_t Revision;
    EFI_PXE_BASE_CODE_START Start;
    EFI_PXE_BASE_CODE_STOP Stop;
    EFI_PXE_BASE_CODE_DHCP Dhcp;
    EFI_PXE_BASE_CODE_DISCOVER Discover;
    EFI_PXE_BASE_CODE_MTFTP Mtftp;
    EFI_PXE_BASE_CODE_UDP_WRITE UdpWrite;
    EFI_PXE_BASE_CODE_UDP_READ UdpRead;
    EFI_PXE_BASE_CODE_SET_IP_FILTER SetIpFilter;
    EFI_PXE_BASE_CODE_ARP Arp;
    EFI_PXE_BASE_CODE_SET_PARAMETERS SetParameters;
    EFI_PXE_BASE_CODE_SET_STATION_IP SetStationIp;
    EFI_PXE_BASE_CODE_SET_PACKETS SetPackets;
    EFI_PXE_BASE_CODE_MODE* Mode;
} EFI_PXE_BASE_CODE_PROTOCOL;

typedef enum { EFI_PXE_BASE_CODE_CALLBACK_STATUS_FIRST, EFI_PXE_BASE_CODE_CALLBACK_STATUS_CONTINUE, EFI_PXE_BASE_CODE_CALLBACK_STATUS_ABORT, EFI_PXE_BASE_CODE_CALLBACK_STATUS_LAST } EFI_PXE_BASE_CODE_CALLBACK_STATUS;

typedef enum {
    EFI_PXE_BASE_CODE_FUNCTION_FIRST,
    EFI_PXE_BASE_CODE_FUNCTION_DHCP,
    EFI_PXE_BASE_CODE_FUNCTION_DISCOVER,
    EFI_PXE_BASE_CODE_FUNCTION_MTFTP,
    EFI_PXE_BASE_CODE_FUNCTION_UDP_WRITE,
    EFI_PXE_BASE_CODE_FUNCTION_UDP_READ,
    EFI_PXE_BASE_CODE_FUNCTION_ARP,
    EFI_PXE_BASE_CODE_FUNCTION_IGMP,
    EFI_PXE_BASE_CODE_PXE_FUNCTION_LAST
} EFI_PXE_BASE_CODE_FUNCTION;

// types for the PXE_BASE_CODE_CALLBACK_PROTOCOL

struct EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL;

typedef EFI_PXE_BASE_CODE_CALLBACK_STATUS(EFIAPI* EFI_PXE_CALLBACK)(IN struct EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL* This, IN EFI_PXE_BASE_CODE_FUNCTION Function, IN bool Received, IN uint32_t PacketLen, IN EFI_PXE_BASE_CODE_PACKET* Packet);

typedef struct EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL {
    uint64_t Revision;
    EFI_PXE_CALLBACK Callback;
} EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL;

#endif // _EFI_PBCP_H
