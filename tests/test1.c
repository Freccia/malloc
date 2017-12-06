

#include <stdlib.h>

#include <unistd.h>

int main()
{
	int i;
	char *addr;

	i = 0;
	write(1, "here.\n", 5);
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		write(1, "here.\n", 5);
		addr[0] = 42;
		i++;
	}
	return (0);
} 
