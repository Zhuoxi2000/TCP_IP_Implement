#ifndef XNET_TINY_H
#define XNET_TINY_H

#include <stdint.h>
#include "xnet_tiny.h"
#define XNET_CFG_PACKET_MAX_SIZE        1516        // �շ����ݰ�������С
#define XNET_MAC_ADDR_SIZE              6           // MAC��ַ����
#define XNET_IPV4_ADDR_SIZE             4           // IP��ַ����
#define XNET_MAC_ADDR_SIZE              6           // MAC��ַ����
#define XNET_CFG_NETIF_IP               {192, 168, 254, 2}  // ��������IP

#pragma pack(1)


/**
 * ��̫������֡��ʽ��RFC894
 */
typedef struct _xether_hdr_t {
    uint8_t dest[XNET_MAC_ADDR_SIZE];           // Ŀ��mac��ַ
    uint8_t src[XNET_MAC_ADDR_SIZE];            // Դmac��ַ
    uint16_t protocol;                          // Э��/����
}xether_hdr_t;

#define XARP_HW_ETHER               0x1         // ��̫��
#define XARP_REQUEST                0x1         // ARP�����
#define XARP_REPLY                  0x2         // ARP��Ӧ��

typedef struct _xarp_packet_t {
    uint16_t hw_type, pro_type;                 // Ӳ�����ͺ�Э������
    uint8_t hw_len, pro_len;                    // Ӳ����ַ�� + Э���ַ��
    uint16_t opcode;                            // ����/��Ӧ
    uint8_t sender_mac[XNET_MAC_ADDR_SIZE];     // ���Ͱ�Ӳ����ַ
    uint8_t sender_ip[XNET_IPV4_ADDR_SIZE];     // ���Ͱ�Э���ַ
    uint8_t target_mac[XNET_MAC_ADDR_SIZE];     // ���շ�Ӳ����ַ
    uint8_t target_ip[XNET_IPV4_ADDR_SIZE];     // ���շ�Э���ַ
}xarp_packet_t;


typedef enum _xnet_err_t {
    XNET_ERR_OK = 0,
    XNET_ERR_IO = -1,
}xnet_err_t;

/**
 * �������ݽṹ
 */
typedef struct _xnet_packet_t {
    uint16_t size;                              // ������Ч���ݴ�С
    uint8_t* data;                             // ����������ʼ��ַ
    uint8_t payload[XNET_CFG_PACKET_MAX_SIZE];  // �����������
}xnet_packet_t;

xnet_packet_t* xnet_alloc_for_send(uint16_t data_size);
xnet_packet_t* xnet_alloc_for_read(uint16_t data_size);

xnet_err_t xnet_driver_open(uint8_t* mac_addr);
xnet_err_t xnet_driver_send(xnet_packet_t* packet);
xnet_err_t xnet_driver_read(xnet_packet_t** packet);

typedef enum _xnet_protocol_t {
    XNET_PROTOCOL_ARP = 0x0806,     // ARPЭ��
    XNET_PROTOCOL_IP = 0x0800,      // IPЭ��
}xnet_protocol_t;



/**
 * IP��ַ
 */
typedef union _xipaddr_t {
    uint8_t array[XNET_IPV4_ADDR_SIZE];     // ��������ʽ�洢��ip
    uint32_t addr;                          // 32λ��ip��ַ
}xipaddr_t;

#define XARP_ENTRY_FREE		        0       // ARP�������

/**
 * ARP����
 */
typedef struct _xarp_entry_t {
    xipaddr_t ipaddr;                       // ip��ַ
    uint8_t	macaddr[XNET_MAC_ADDR_SIZE];    // mac��ַ
    uint8_t	state;                          // ״̬λ
    uint16_t tmo;                           // ��ǰ��ʱ
    uint8_t	retry_cnt;                      // ��ǰ���Դ���
}xarp_entry_t;

void xarp_init(void);
int xarp_make_request(const xipaddr_t* mac_addr);

void xnet_init(void);
void xnet_poll(void);

#endif // XNET_TINY_H