#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main()
{
	size_t x = 12;

	ft_putnbr((x - 1) & -x);
	ft_putnbr(11 & -12);
	return (0);
} 
