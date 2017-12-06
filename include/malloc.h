/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:12:42 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/04 20:57:06 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// https://www.cocoawithlove.com/2010/05/look-at-how-malloc-works-on-mac.html
// http://manpagesfr.free.fr/man/man2/mmap.2.html

#ifndef MALLOC_H
# define MALLOC_H

# include <stdint.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include "libft.h"
//# include <pthread.h>

# define PROT			PROT_READ | PROT_WRITE
# define MAP			MAP_ANON | MAP_PRIVATE

/*
** # define PAGE_SIZE		(unsigned int)sysconf(_SC_PAGESIZE) // Linux
*/
# define PAGE_SIZE		(size_t)getpagesize()
# define META_SIZE		sizeof(t_meta)

# define TINY_SIZE		(size_t)PAGE_SIZE * 2
# define SMALL_SIZE		(size_t)PAGE_SIZE * 16
# define TINY_AREA		(size_t)(TINY_SIZE + META_SIZE)
# define SMALL_AREA		(size_t)(SMALL_SIZE + META_SIZE)
# define TINY_ZONE		(size_t)(TINY_SIZE + META_SIZE) * 100
# define SMALL_ZONE		(size_t)(SMALL_SIZE + META_SIZE) * 100

/*
 **  Structures
 */
typedef struct  s_page	t_page;
typedef struct  s_meta	t_meta;

struct  s_meta
{
	//t_list		next;
	t_meta		*next;
	uint8_t		free;
	size_t		size;
	void		*data;
};

struct  s_page
{
	struct s_meta *tiny;
	struct s_meta *small;
	struct s_meta *large;
	struct s_meta *tiny_last;
	struct s_meta *small_last;
	struct s_meta *large_last;
};

/*
 **  Globals
 */
t_page          	g_mem;
//pthread_mutex_t		g_mem_mutex;

/*
 **  Functions prototypes
 */
void            free(void *ptr);
void            *malloc(size_t size);
void            *realloc(void *ptr, size_t size);
//void			*calloc(size_t size);
void            show_alloc_mem();

/*
**	Alloc_mem
*/
t_meta			*mmap_zone_tiny();
t_meta			*mmap_zone_small();
void			*alloc_mem_tiny(size_t size);
void			*alloc_mem_small(size_t size);
void			*alloc_mem_large(size_t size);

/*
**	Utils
*/
t_meta			*find_free_chunk(t_meta *mem, size_t size);
void			update_last_chunk(t_meta **last, t_meta *mem);
void			update_meta_info(t_meta **mem, size_t chunk_size);

#endif
