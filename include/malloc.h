

#ifndef FT_MALLOC
#define FT_MALLOC

#include <stdlib.h>
#include <sys/mman.h>
#include "libft.h"

/*
**
** Chaque zone doit pouvoir contenir au moins 100 allocations.
**     - Les mallocs “TINY”, de 1 à n octets, 
**        seront stockés dans des zones de N octets
**     - Les mallocs “SMALL”, de (n+1) à m octets,
**        seront stockés dans des zones de M octets
**     - Les mallocs “LARGE”, de (m+1) octets et plus,
**        seront stockés hors zone, c’est à dire simplement
**        avec un mmap(), ils seront en quelquesorte une 
**        zone à eux tout seul.
**
*/

// Useful: http://g.oswego.edu/dl/html/malloc.html

#	define PAGE_SIZE				(unsigned int)getpagesize()
# define META_SIZE				(unsigned int)sizeof(t_block)

# define TINY							PAGE_SIZE * 4
# define SMALL						PAGE_SIZE * 12

typedef struct	s_block		t_block;
typedef struct	s_chunk		t_chunk;

/*
**	t_chunk represent the chunk's metadata in which 
**		a t_block is divided.
*/

struct	s_chunk
{
	size_t				size;
	bool					free;
};

/*
**	t_block is the allocated area got by mmap.
**		the block of size TINY, SMALL or LARGE,
**			and it will be splitted in chunks.
*/

struct	s_block
{
  size_t				size;
  bool					full;
  t_block				*next;
  t_block				*prev;
	void					*data;
};

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		*show_alloc_mem();

#endif
