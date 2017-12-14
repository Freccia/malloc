#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main()
{
		void    *mem;

		mem = calloc(10, 10);
		ft_putendl("----------------------");
		show_alloc_mem();
		ft_putendl("----------------------");
		mem = realloc(mem, 100);
		ft_putendl("----------------------");
		show_alloc_mem();
		ft_putendl("----------------------");
		mem = realloc(mem, 200);
		ft_putendl("----------------------");
		show_alloc_mem();
		ft_putendl("----------------------");
		mem = realloc(mem, 50);
		show_alloc_mem();
		return (0);
} 
