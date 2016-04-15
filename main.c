/**
 * main.c
 *
 * Detecting memory leaks only for windows .  
 * Place the following snippet where leak to be tested: 
 * #if defined(_CRTDBG_MAP_ALLOC) 
 *    _CrtDumpMemoryLeaks(); 
 * #endif 
 */  
#if defined(WIN32) && defined(_DEBUG)  
  #ifndef   _CRTDBG_MAP_ALLOC  
    #pragma message( __FILE__": _CRTDBG_MAP_ALLOC defined only for DEBUG on Win32." )   
    #define _CRTDBG_MAP_ALLOC  
    #include<stdlib.h>   
    #include<crtdbg.h>  
  #endif  
#endif  

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashmap.h"

typedef struct userelem_t {
  char   key[20];
  char  *value;
} userelem;

#if 0
typedef struct userdata_t {
  char   name[20];
  hmap_t map;  /* userelem map */
} userdata;
#endif


static int iter_elem(void* elem, void *arg) {
  userelem *el = (userelem *) elem;
  printf("key=%s; value=%s\n", el->key, el->value);
  return 0;
}

static int free_elem(void* elem, void *arg) {
	userelem *el = (userelem *) elem;
	free(el->value);
	free(el);
	return 0;
}

static int free_data(void* data, void *arg) {
	//userdata *dat = (userdata *) data;
	/* 删除整个子 map */
	//hashmap_destroy(dat->map, free_elem, 0);
	free(data);
	return 0;
}

int create_hashtable(hmap_t* map, int size)
{
	*map = hashmap_create();
	return HMAP_S_OK;
}

int delete_hashtable(hmap_t map)
{
	hashmap_destroy(map, free_data, 0);
	return HMAP_S_OK;
}


int add_mac_in_hashtable(hmap_t map, char* mac, int value){

	userelem *dat, *dat1;
	int ret, i = 10;

	dat = (userelem *)malloc(sizeof(userelem));
	sprintf(dat->key, "%s", mac);
	dat->value = (char*) malloc(30);
	sprintf(dat->value, "%d", value);
	ret = hashmap_put(map, dat->key, dat);
	if(ret == HMAP_E_KEYUSED)
	{
		ret = hashmap_remove(map, dat->key, &dat1);
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


int main(int argc, char* argv[])
{
	hmap_t map;
	int ret;
	int i;
	char mac[]="000e1e1013";
	
	ret = create_hashtable(&map, 100);
	assert(ret==HMAP_S_OK);

  	for (i=10; i<100; i++) {
		sprintf(mac, "000e1e10%d", i);
		add_mac_in_hashtable(map, mac, i);
	}
	printf("Hashtable len=%d\n", get_hashtable_length(map));
	print_hashtable(map);

	add_mac_in_hashtable(map, "000e1e1099", i);

	printf("Hashtable len=%d\n", get_hashtable_length(map));
	print_hashtable(map);

	delete_hashtable(map);

	return 0;
}


#if 0

int main(int argc, char* argv[])
{
  hmap_t map;
  //userdata  *dat;
  userelem  *el, *dat, *dat1;
  int ret, i;

  /* 创建 hashmap */
  map = hashmap_create();

#if 0
  /* 插入 hashmap 元素 */
  for (i=0; i<100; i++) {
	  el = (userelem *)malloc(sizeof(userelem));
	  sprintf(el->key, "%d", i);
	  el->value = (char*) malloc(30);
	  sprintf(el->value, "%d", i+1000);
	  ret = hashmap_put(map, el->key, el);
	  assert(ret==HMAP_S_OK);
  }
#endif
  printf("hashmap_size: %d\n", hashmap_size(map));
#if 0
	  dat = (userelem *)malloc(sizeof(userelem));
	  sprintf(dat->key, "%d", 16);
	  dat->value = (char*) malloc(30);
	  sprintf(dat->value, "%d", 0xcafe);
	  ret = hashmap_put(map, dat->key, dat);
	  if(ret == HMAP_E_KEYUSED)
	  {
		  ret = hashmap_remove(map, dat->key, &dat1);
		  free_elem(dat1, 0);
	  }
	  ret = hashmap_put(map, dat->key, dat);
	  assert(ret==HMAP_S_OK);
#endif

#if 0
  /* 删除指定元素: key="10" */
  ret = hashmap_remove(map, "10", &dat);
  assert(ret==HMAP_S_OK);
  printf("hashmap_remove: name=%s. size=%d\n", dat->name, hashmap_size(map));
  hashmap_iterate(dat->map, iter_elem, 0);
  free_data(dat, 0);

  /* 删除指定元素: key="11" */
  ret = hashmap_remove(map, "11", &dat);
  assert(ret==HMAP_S_OK);
  printf("hashmap_remove: name=%s. size=%d\n", dat->name, hashmap_size(map));
  hashmap_iterate(dat->map, iter_elem, 0);
  free_data(dat, 0);

  /* 查询元素: key="99" */
  ret = hashmap_get(map, "99", &dat);
  assert(ret==HMAP_S_OK);
  printf("hashmap_get: name=%s. size=%d\n", dat->name, hashmap_size(map));
  hashmap_iterate(dat->map, iter_elem, 0);
#endif
  /* 删除整个 map */
//  hashmap_destroy(map, free_data, 0);

//  _CrtDumpMemoryLeaks();
  return 0;
}
#endif

