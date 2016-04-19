/**
 * main.c
 *
 */  
#include <stdio.h>
#include "hashmaplib.h"
int main(void)
{
	hmap_t map;
	int i;
	unsigned char mac[]="000e1e1013";
	
	create_hashtable(&map);
	//assert(ret==HMAP_S_OK);

  	for (i=10; i<100; i++) {
		sprintf((char*) mac, "000e1e10%d", i);
		add_mac_in_hashtable(map, mac, i);
	}
	printf("Hashtable len=%d\n", get_hashtable_length(map));
	print_hashtable(map);

	sprintf((char*) mac, "000e1e10%d", 99);

	add_mac_in_hashtable(map, mac, i);

	printf("Hashtable len=%d\n", get_hashtable_length(map));
	print_hashtable(map);

	delete_hashtable(map);

	return 0;
}
