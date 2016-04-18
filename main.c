/**
 * main.c
 *
 */  
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashmap.h"

#define UNUSED(expr) do { (void)(expr); } while (0)

typedef struct userelem_t {
  unsigned char   key[20];
  unsigned char  *value;
} userelem;

static int iter_elem(void* elem, void *arg) {
  userelem *el = (userelem *) elem;
  UNUSED(arg);
  printf("key=%s; value=%s\n", el->key, el->value);
  return 0;
}

static int free_elem(void* elem, void *arg) {
	userelem *el = (userelem *) elem;
	UNUSED(arg);
	free(el->value);
	free(el);
	return 0;
}

static int free_data(void* data, void *arg) {
	UNUSED(arg);
	free(data);
	return 0;
}

int create_hashtable(hmap_t* map)
{
	*map = hashmap_create();
	return HMAP_S_OK;
}

int delete_hashtable(hmap_t map)
{
	hashmap_destroy(map, free_data, 0);
	return HMAP_S_OK;
}


int add_mac_in_hashtable(hmap_t map, unsigned char* mac, int value){

	userelem *dat = NULL, *dat1 = NULL;
	int ret = 0;

	dat = (userelem *)malloc(sizeof(userelem));
	sprintf((char*) dat->key, "%s", mac);
	dat->value = (unsigned char*) malloc(30);
	sprintf((char*) dat->value, "%d", value);
	ret = hashmap_put(map, dat->key, dat);
	if(ret == HMAP_E_KEYUSED)
	{
		ret = hashmap_remove(map, dat->key, (void_ptr) &dat1);
		assert(ret==HMAP_S_OK);
		free_elem(dat1, 0);
		ret = hashmap_put(map, dat->key, dat);
	}
	assert(ret==HMAP_S_OK);
	return ret;
}

int get_hashtable_length(hmap_t map){
	return hashmap_size(map);
}

int print_hashtable(hmap_t map)
{
  return hashmap_iterate(map, iter_elem, 0);
}


int main(void)
{
	hmap_t map;
	int ret;
	int i;
	unsigned char mac[]="000e1e1013";
	
	ret = create_hashtable(&map);
	assert(ret==HMAP_S_OK);

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
