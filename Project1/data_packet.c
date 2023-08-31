#include "data_packet.h"


static data_packet_def send_packet, recieve_packet;
data_packet_def* data_packet_malloc_forsend(uint8_t size)
{
	send_packet.data = send_packet.data_load + 1156 - size;
	send_packet.size = size;
	return &send_packet;
}

data_packet_def* data_packet_malloc_forrecive(uint8_t size)
{
	recieve_packet.data = recieve_packet.data_load ;
	recieve_packet.size = size;
	return &recieve_packet;
}

static void add_header(data_packet_def* packet, uint8_t header_size)
{
	packet->data -= header_size;
	packet->size += header_size;
}

static void remove_header(data_packet_def* packet, uint8_t header_size)
{
	packet->data += header_size;
	packet->size -= header_size;
}

void packet_init(void)
{

}
void packet_poll(void)
{

}