#include "malloc.h"

void	*malloc(size_t size)
{
		void	*chunk;

		return (chunk);
}

void* mymalloc(size_t len)
{
		void* addr = mmap(0, len + sizeof(size_t),
						PROT_READ | PROT_WRITE,
						MAP_ANON | MAP_PRIVATE, -1, 0);
		*(size_t*)addr = len;

		return (addr + sizeof(size_t));
}

int myfree(void* addr)
{
		return (munmap(addr - sizeof(size_t), (size_t) addr));
}


