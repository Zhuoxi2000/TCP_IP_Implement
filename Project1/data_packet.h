
#include<stdint.h>

typedef struct data_packet_def
{
	uint8_t size; // current data size 
	uint8_t* data;
	uint8_t data_load[1156];

}data_packet_def;

data_packet_def* data_packet_malloc_forsend(uint8_t size);
data_packet_def* data_packet_malloc_forrecive(uint8_t size);

void packet_init(void);
void packet_poll(void);