#include"data_packet.h"



int main(void)
{
	packet_init();
	while (1)
	{
		packet_poll();
	}

	return 0;
}

