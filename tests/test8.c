#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main()
{
	char *str;
	void *ptr;

	str = calloc(5, 10);
	strcpy(str, "Hello World!\n");
	ptr = malloc(100);
	memset(ptr, 'a', 100);
	show_alloc_mem_ex();
	free(ptr);
	ptr = calloc(10, 10);
	show_alloc_mem_ex();
	free(ptr);
	return (0);
} 
