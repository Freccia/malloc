#include <stdlib.h>
#include "malloc.h"

int main()
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
	void *addr0, *addr1, *addr2, *addr3, *addr4;

	addr0 = malloc(1024);
	addr1 = malloc(1024 * 32);
	addr2 = malloc(1024 * 1024);
	addr3 = malloc(1024 * 1024 * 16);
	addr4 = malloc(1024 * 1024 * 128);
#pragma clang diagnostic pop
	write(1, "--------------------", 20);
	show_alloc_mem();
	write(1, "--------------------", 20);
	free(addr0);
	free(addr1);
	free(addr2);
	free(addr3);
	free(addr4);
	write(1, "--------------------", 20);
	show_alloc_mem();
	write(1, "--------------------", 20);
	return (0);
} 
