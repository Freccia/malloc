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
	ft_putendl("---------------------------");
	show_alloc_mem_ex();
	ft_putendl("\n---------------------------");
	str = realloc(str, 1024 * 2);
	if ((ptr = realloc(ptr, 1024 * 3)) == NULL)
		ft_putendl("RETURNED NULL");
	ft_putendl("---------------------------");
	show_alloc_mem_ex();
	ft_putendl("\n---------------------------");
	free(ptr);
	return (0);
} 
