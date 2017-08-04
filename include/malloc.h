

#ifndef FT_MALLOC
# define FT_MALLOC

# include <stdint.h>
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

// Useful:
// http://g.oswego.edu/dl/html/malloc.html
// https://danluu.com/malloc-tutorial

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

/*
**	Structures
*/

/*
**	`t_chunk` represent the chunk's metadata in which 
**		a t_page is divided.
*/

/*
**	`t_page` is the metadata about allocated area got by mmap.
**		The pages's size is TINY, SMALL or LARGE,
**			and it will be splitted in chunks.
*/

typedef struct	s_page		t_page;
typedef struct	s_chunk		t_chunk;

struct	s_chunk
{
	uint8_t				free;
	size_t				size;
};

struct	s_page
{
  uint8_t				full;
	size_t				size;
	size_t				size_left;
  t_page				*next;
	t_chunk				first;
};

/*
**	Globals
*/

t_page					*g_mem;
extern t_page		*g_mem;

/*
**	Functions definitions
*/

void						free(void *ptr);
void						*malloc(size_t size);
void						*realloc(void *ptr, size_t size);
void						show_alloc_mem();

#endif
