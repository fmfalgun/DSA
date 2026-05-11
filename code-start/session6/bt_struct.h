#ifndef BT_STRUCT_H
#define BT_STRUCT_H
#include <stdint.h>

struct BT_NODE{
	char	 address[18];
	char	 address_type[8];
	char	 name[64];
	char	 alias[64];
	uint32_t bt_class;
	char 	 icon[32];
	int	 paired;
	int	 bonded;
	int  	 trusted;
	int  	 blocked;
	int 	 legacy_pairing;
	int 	 cable_pairing;
	int 	 connected;
	int	 services_resolved;
	char	 uuids[16][37];
	int 	 uuid_count;
	char	 adapter[32];
	int16_t	 rssi;
	char 	 protocol[16];	
};

#endif
