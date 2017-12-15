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
		ft_putendl("---ONE----------------");
		show_alloc_mem();
		ft_putendl("---ONE----------------");
		mem = realloc(mem, 100);
		memset(mem, 'w', 100);
		ft_putendl("---TWO----------------");
		show_alloc_mem();
		ft_putendl("---TWO----------------");
		mem = realloc(mem, 200);
		memset(mem, 'e', 200);
		ft_putendl("---THREE--------------");
		show_alloc_mem_ex();
		ft_putendl("---THREE--------------");
		mem = realloc(mem, 50);
		memset(mem, 'r', 50);
		ft_putendl("---FOUR---------------");
		show_alloc_mem();
		ft_putendl("---FOUR---------------");
		mem = realloc(mem, 60);
		memset(mem, 'r', 60);
		ft_putendl("---FIVE---------------");
		show_alloc_mem();
		ft_putendl("---FIVE---------------");
		free(mem);
		return (0);
} 
