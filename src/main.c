
#include <stdio.h>		//norme
#include <unistd.h>		//norme
#include "malloc.h"

void	*mymalloc(size_t len);
int		myfree(void *addr);

int main(int ac, char **av)
{
		int		gpsz = getpagesize();
		long	sysz = sysconf(_SC_PAGESIZE);

		(void)ac;
		(void)av;

		ft_printf("gpsz: %d\n", gpsz);
		ft_printf("sysz: %d\n", sysz);

		ft_putstr("Allocating space...\n");
		char *heap_chunk = mymalloc(sizeof(15));

		ft_putstr("Writing to allocated space...\n");
		heap_chunk = strcpy(heap_chunk, "LOLOLOLOLOL");

		ft_putstr("Reading from allocated space...\n");
		ft_printf("%s\n", heap_chunk);
		printf("addr: %p\n", &heap_chunk);

		ft_putendl("----------------------------------");
		show_alloc_mem();
		ft_putendl("----------------------------------");

		ft_putstr("Allocating space...\n");
		heap_chunk = mymalloc(sizeof(200));

		ft_putstr("Writing to allocated space...\n");
		heap_chunk = strcpy(heap_chunk, "LOLOLOLOLOLOLOLOLO\
						LOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");

		ft_putstr("Reading from allocated space...\n");
		ft_printf("%s\n", heap_chunk);
		printf("addr: %p\n", &heap_chunk);

		ft_putendl("----------------------------------");
		show_alloc_mem();
		ft_putendl("----------------------------------");


		ft_putstr("Freeing allocated space\n");
		myfree(heap_chunk);

		ft_putendl("----------------------------------");
		show_alloc_mem();
		ft_putendl("----------------------------------");


//	leaks
//		while (1);

		return (0);
}

