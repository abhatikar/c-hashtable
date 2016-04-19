#ifndef _MAIN_H_INCLUDED
#define _MAIN_H_INCLUDED

typedef void* void_ptr;
typedef void_ptr hmap_t;

int create_hashtable(hmap_t* map);
int delete_hashtable(hmap_t map);
int add_mac_in_hashtable(hmap_t map, unsigned char* mac, int value);
int get_hashtable_length(hmap_t map);
int print_hashtable(hmap_t map);

#endif // _MAIN_H_INCLUDED
