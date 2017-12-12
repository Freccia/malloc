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
	show_alloc_mem_ex();
	free(ptr);
	show_alloc_mem_ex();
	return (0);
} 
