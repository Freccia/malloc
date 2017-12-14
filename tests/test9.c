#include <stdlib.h>
#include <string.h>
#include "malloc.h"

/*
**	This tests if memalign is correct
*/

int main()
{
	char	*str;
	void	*ptr;
	size_t	align = 4;

	if ((str = memalign(16, 30)) != NULL)
	{
		strcpy(str, "Hello World!\n");
		if ((uintptr_t)ptr % align)
			ft_putendl("STR: NON ALIGNED");
	}
	else
		ft_putendl("RETURNED NULL");
	if ((ptr = memalign(align, 100)) != NULL)
	{
		strcpy(ptr, "yeyeyeyeyeyyeyeyeyeyey\n");
		if ((uintptr_t)ptr % align)
			ft_putendl("PTR: NON ALIGNED");
		else
			ft_memset(ptr, 'a', 50);
	}
	else
		ft_putendl("RETURNED NULL");
	ft_putendl("---------------------------------");
	show_alloc_mem_ex();
	ft_putendl("\n---------------------------------");
	ft_putendl("\n---------------------------------");
	free(ptr);
	show_alloc_mem_ex();
	ft_putendl("\n---------------------------------");
	return (0);
} 
