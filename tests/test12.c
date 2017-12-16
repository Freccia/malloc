#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "malloc.h"

#define M (1)

/*
**	Tests realloc
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

  addr1 = (char*)malloc(16*M);
  strcpy(addr1, "Bonjours\n");
  print(addr1);
  addr2 = (char*)malloc(16*M);
  ft_putendl("-------------------------------");
  show_alloc_mem();
  ft_putendl("-------------------------------");
  if ((addr3 = (char*)realloc(addr1, 128*M)) == NULL)
  {
	  ft_putendl("RETURNED NULL");
	  return (1);
  }
  addr3[127*M] = 42;
  print(addr3);
  return (0);
} 
