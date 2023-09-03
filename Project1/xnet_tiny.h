#ifndef XNET_TINY_H
#define XNET_TINY_H

#include <stdint.h>

#define XNET_CFG_PACKET_MAX_SIZE        1516        // �շ����ݰ�������С

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

void xnet_init(void);
void xnet_poll(void);

#endif // XNET_TINY_H