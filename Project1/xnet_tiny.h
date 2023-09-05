#ifndef XNET_TINY_H
#define XNET_TINY_H

#include <stdint.h>
#include "xnet_tiny.h"
#define XNET_CFG_PACKET_MAX_SIZE        1516        // 收发数据包的最大大小
#define XNET_MAC_ADDR_SIZE              6           // MAC地址长度
#define XNET_IPV4_ADDR_SIZE             4           // IP地址长度
#define XNET_MAC_ADDR_SIZE              6           // MAC地址长度
#define XNET_CFG_NETIF_IP               {192, 168, 254, 2}  // 本机网卡IP

#pragma pack(1)


/**
 * 以太网数据帧格式：RFC894
 */
typedef struct _xether_hdr_t {
    uint8_t dest[XNET_MAC_ADDR_SIZE];           // 目标mac地址
    uint8_t src[XNET_MAC_ADDR_SIZE];            // 源mac地址
    uint16_t protocol;                          // 协议/长度
}xether_hdr_t;

#define XARP_HW_ETHER               0x1         // 以太网
#define XARP_REQUEST                0x1         // ARP请求包
#define XARP_REPLY                  0x2         // ARP响应包

typedef struct _xarp_packet_t {
    uint16_t hw_type, pro_type;                 // 硬件类型和协议类型
    uint8_t hw_len, pro_len;                    // 硬件地址长 + 协议地址长
    uint16_t opcode;                            // 请求/响应
    uint8_t sender_mac[XNET_MAC_ADDR_SIZE];     // 发送包硬件地址
    uint8_t sender_ip[XNET_IPV4_ADDR_SIZE];     // 发送包协议地址
    uint8_t target_mac[XNET_MAC_ADDR_SIZE];     // 接收方硬件地址
    uint8_t target_ip[XNET_IPV4_ADDR_SIZE];     // 接收方协议地址
}xarp_packet_t;


typedef enum _xnet_err_t {
    XNET_ERR_OK = 0,
    XNET_ERR_IO = -1,
}xnet_err_t;

/**
 * 网络数据结构
 */
typedef struct _xnet_packet_t {
    uint16_t size;                              // 包中有效数据大小
    uint8_t* data;                             // 包的数据起始地址
    uint8_t payload[XNET_CFG_PACKET_MAX_SIZE];  // 最大负载数据量
}xnet_packet_t;

xnet_packet_t* xnet_alloc_for_send(uint16_t data_size);
xnet_packet_t* xnet_alloc_for_read(uint16_t data_size);

xnet_err_t xnet_driver_open(uint8_t* mac_addr);
xnet_err_t xnet_driver_send(xnet_packet_t* packet);
xnet_err_t xnet_driver_read(xnet_packet_t** packet);

typedef enum _xnet_protocol_t {
    XNET_PROTOCOL_ARP = 0x0806,     // ARP协议
    XNET_PROTOCOL_IP = 0x0800,      // IP协议
}xnet_protocol_t;



/**
 * IP地址
 */
typedef union _xipaddr_t {
    uint8_t array[XNET_IPV4_ADDR_SIZE];     // 以数据形式存储的ip
    uint32_t addr;                          // 32位的ip地址
}xipaddr_t;

#define XARP_ENTRY_FREE		        0       // ARP表项空闲

/**
 * ARP表项
 */
typedef struct _xarp_entry_t {
    xipaddr_t ipaddr;                       // ip地址
    uint8_t	macaddr[XNET_MAC_ADDR_SIZE];    // mac地址
    uint8_t	state;                          // 状态位
    uint16_t tmo;                           // 当前超时
    uint8_t	retry_cnt;                      // 当前重试次数
}xarp_entry_t;

void xarp_init(void);
int xarp_make_request(const xipaddr_t* mac_addr);

void xnet_init(void);
void xnet_poll(void);

#endif // XNET_TINY_H