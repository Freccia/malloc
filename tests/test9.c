#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main()
{
	char	*str;
	void	*ptr;
	size_t	align = 4;

	str = memalign(16, 30);
	strcpy(str, "Hello World!\n");
	if ((ptr = memalign(align, 100)) == NULL)
	{
		ft_putendl("NULL");
	}
	else if ((uintptr_t)ptr % align)
		ft_putendl("NON ALIGNED");
	else
		ft_memset(ptr, 'a', 3);
	show_alloc_mem_ex();
	free(ptr);
	show_alloc_mem_ex();
	return (0);
} 
