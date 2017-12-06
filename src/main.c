
#include <stdio.h>		//norme
#include <unistd.h>		//norme
#include "malloc.h"

int main(int ac, char **av)
{
		int		gpsz = getpagesize();
		long	sysz = sysconf(_SC_PAGESIZE);

		(void)ac;
		(void)av;

		ft_printf("gpsz: %d\n", gpsz);
		ft_printf("sysz: %d\n", sysz);

		
    	//ft_printf("CHUNK_META: %ld\n", CHUNK_META);
    	//ft_printf("PAGE_META: %ld\n", PAGE_META);
    	//ft_printf("chunk_t: %ld\n", sizeof(t_chunk));
    	ft_printf("uint8_t: %ld\n", sizeof(uint8_t));
    	ft_printf("size_t: %ld\n", sizeof(size_t));

		ft_printf("TINY_SIZE: %ld\n", TINY_SIZE);
		ft_printf("SMALL_SIZE: %ld\n", SMALL_SIZE);
		ft_printf("TINY_ZONE: %ld\n", TINY_ZONE);
		ft_printf("SMALL_ZONE: %ld\n", SMALL_ZONE);

		ft_putstr("Allocating space...\n");
		char *heap_chunk = malloc(18);

		ft_putstr("Writing to allocated space...\n");
		heap_chunk = strcpy(heap_chunk, "SDACLOLOLOLOLOLFRG");

		ft_putstr("Reading from allocated space...\n");
		ft_printf("%s\n", heap_chunk);

		ft_putendl("----------------------------------");
		show_alloc_mem();
		ft_putendl("----------------------------------");

		ft_putstr("Allocating space...\n");
		heap_chunk = malloc(200);

		ft_putstr("Writing to allocated space...\n");
		heap_chunk = strcpy(heap_chunk, "LOLOLOLOLOLOLOLOLO\
LOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");

		ft_putstr("Reading from allocated space...\n");
		ft_printf("%s\n", heap_chunk);

		ft_putendl("----------------------------------");
		show_alloc_mem();
		ft_putendl("----------------------------------");


		ft_putstr("Freeing allocated space\n");
		free(heap_chunk);

		ft_putendl("----------------------------------");
		show_alloc_mem();
		ft_putendl("----------------------------------");


//	leaks
//		while (1);

		return (0);
}

