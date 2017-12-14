#include <stdlib.h>
#include <string.h>
#include "malloc.h"

/*
**	Test calloc - realloc
*/

int main()
{
		void    *mem;

		mem = calloc(10, 10);
		memset(mem, 'q', 100);
		ft_putendl("----------------------");
		show_alloc_mem();
		ft_putendl("----------------------");
		mem = realloc(mem, 100);
		memset(mem, 'w', 100);
		ft_putendl("----------------------");
		show_alloc_mem();
		ft_putendl("----------------------");
		mem = realloc(mem, 200);
		memset(mem, 'e', 200);
		ft_putendl("----------------------");
		show_alloc_mem_ex();
		ft_putendl("----------------------");
		mem = realloc(mem, 50);
		memset(mem, 'r', 50);
		show_alloc_mem();
		free(mem);
		return (0);
} 
