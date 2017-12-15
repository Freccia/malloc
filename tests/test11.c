#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "malloc.h"

#define M (1024 * 1024)

/*
**	Tests allocation history
*/

void print(char *s)
{
		write(1, s, strlen(s));
}

int main()
{
		char *addr1;
		char *addr2;
		char *addr3;

		addr1 = (char*)malloc(30);
		strcpy(addr1, "Bonjours\n");
		print(addr1);
		addr2 = (char*)malloc(1000);
		if ((addr3 = (char*)realloc(addr1, 128)) != NULL)
		{
			addr3[10] = 42;
			print(addr3);
		}
		addr1 = (char*)calloc(40, 60);
		strcpy(addr1, "Bonjours\n\0");
		print(addr1);
		free(addr2);
		free(addr1);
		free(addr3);

		ft_putendl("----- ALLOCATION HISTORY --------------");
		print_allocation_history();
		ft_putendl("---------------------------------------");
		return (0);
} 
