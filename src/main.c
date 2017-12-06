
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

		
    	ft_printf("CHUNK_META: %ld\n", CHUNK_META);
    	ft_printf("PAGE_META: %ld\n", PAGE_META);
    	ft_printf("chunk_t: %ld\n", sizeof(t_chunk));
    	ft_printf("uint8_t: %ld\n", sizeof(uint8_t));
    	ft_printf("size_t: %ld\n", sizeof(size_t));

		ft_printf("TINY: %ld\n", TINY);
		ft_printf("SMALL: %ld\n", SMALL);
		ft_printf("PAGE_TINY: %ld\n", PAGE_TINY);
		ft_printf("PAGE_SMALL: %ld\n", PAGE_SMALL);

		ft_putstr("Allocating space...\n");
		char *heap_chunk = mymalloc(18);

		ft_putstr("Writing to allocated space...\n");
		heap_chunk = strcpy(heap_chunk, "SDACLOLOLOLOLOLFRG");

		ft_putstr("Reading from allocated space...\n");
		ft_printf("%s\n", heap_chunk);

		ft_putendl("----------------------------------");
		show_alloc_mem();
		ft_putendl("----------------------------------");

		ft_putstr("Allocating space...\n");
		heap_chunk = mymalloc(200);

		ft_putstr("Writing to allocated space...\n");
		heap_chunk = strcpy(heap_chunk, "LOLOLOLOLOLOLOLOLO\
LOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");

		ft_putstr("Reading from allocated space...\n");
		ft_printf("%s\n", heap_chunk);

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

