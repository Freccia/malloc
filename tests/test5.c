#include <stdlib.h>
#include "malloc.h"

int main()
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
  malloc(1024);
  malloc(1024 * 32);
  malloc(1024 * 1024);
  malloc(1024 * 1024 * 16);
  malloc(1024 * 1024 * 128);
#pragma clang diagnostic pop
  show_alloc_mem();
  return (0);
} 
