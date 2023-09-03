#ifndef XNET_TINY_H
#define XNET_TINY_H

#include <stdint.h>

#define XNET_CFG_PACKET_MAX_SIZE        1516        // �շ����ݰ�������С

#define XNET_MAC_ADDR_SIZE              6           // MAC��ַ����

/**
 * ��̫������֡��ʽ��RFC894
 */
typedef struct _xether_hdr_t {
    uint8_t dest[XNET_MAC_ADDR_SIZE];           // Ŀ��mac��ַ
    uint8_t src[XNET_MAC_ADDR_SIZE];            // Դmac��ַ
    uint16_t protocol;                          // Э��/����
}xether_hdr_t;


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


void xnet_init(void);
void xnet_poll(void);

#endif // XNET_TINY_H