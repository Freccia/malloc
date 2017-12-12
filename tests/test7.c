#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main()
{
	char *str;
	void *ptr;

	str = malloc(30);
	strcpy(str, "Hello World!\n");
	ptr = malloc(100);
	memset(ptr, 'a', 100);
	//malloc(1024);
	//malloc(1024 * 22);
	//  malloc(1024 * 1024);
	//  malloc(1024 * 1024 * 16);
	//  malloc(1024 * 1024 * 128);
	show_alloc_mem_ex();
	free(ptr);
	show_alloc_mem_ex();
	return (0);
} 
