

#ifndef FT_MALLOC
# define FT_MALLOC

# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include "libft.h"

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

//#	define PAGE_SIZE				(unsigned int)getpagesize()
#	define PAGE_SIZE				(unsigned int)sysconf(_SC_PAGESIZE)
# define META_SIZE				(unsigned int)sizeof(t_block)

# define TINY							PAGE_SIZE * 4
# define SMALL						PAGE_SIZE * 12

# ifndef TRUE
# 	define TRUE							1
# endif
# ifndef FALSE
#		define FALSE						0
# endif

typedef struct	s_page		t_page;
typedef struct	s_chunk		t_chunk;

/*
**	t_chunk represent the chunk's metadata in which 
**		a t_block is divided.
*/

struct	s_chunk
{
	int						free;
	size_t				size;
};

/*
**	t_block is the allocated area got by mmap.
**		The block's size is TINY, SMALL or LARGE,
**			and it will be splitted in chunks.
*/

struct	s_page
{
  int						full;
	size_t				size;
	size_t				size_left;
  t_page				*next;
	t_chunk				first;
};

t_page					*g_mem;
extern t_page		*g_mem;

void						free(void *ptr);
void						*malloc(size_t size);
void						*realloc(void *ptr, size_t size);
void						*show_alloc_mem();

#endif
