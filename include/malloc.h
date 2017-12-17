/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:36:20 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/17 16:36:49 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdint.h>
# include <sys/mman.h>
# include "libft.h"
# include <pthread.h>

# define _PROT			PROT_READ | PROT_WRITE
# define _MAP			MAP_PRIVATE | MAP_ANONYMOUS

# define PAGE_SIZE		getpagesize()
# define META_SIZE		sizeof(t_chunk)

# define TINY_SIZE		(size_t)PAGE_SIZE * 2
# define SMALL_SIZE		(size_t)PAGE_SIZE * 16

# define TINY_ZONE		(size_t)(TINY_SIZE + META_SIZE) * 100
# define SMALL_ZONE		(size_t)(SMALL_SIZE + META_SIZE) * 100

typedef struct s_chunk		t_chunk;
typedef struct s_page		t_page;

struct	s_chunk
{
	t_chunk		*next;
	size_t		size;
	uint8_t		free;
	void		*data;
};

struct	s_page
{
	t_chunk		*tiny;
	t_chunk		*small;
	t_chunk		*large;
	t_chunk		*tiny_last;
	t_chunk		*small_last;
	t_chunk		*large_last;
};

t_page			g_mem;

void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			free(void *ptr);
void			show_alloc_mem(void);

/*
**	Alloc
*/
void			*alloc_mem_tiny(size_t size);
void			*alloc_mem_small(size_t size);
void			*alloc_mem_large(size_t size);

/*
**	Find
*/
t_chunk			*find_free_chunk(size_t size, t_chunk *list);
t_chunk			*find_memory_chunk(void *ptr);

/*
**	Utils
*/
void			join_free_chunks(void);
void			_init_memory_chunk(t_chunk **mem, size_t size, \
		size_t zone_size);
void			_update_meta_info(t_chunk **mem, size_t size);
t_chunk			*find_mem_chunk(size_t size, t_chunk *list);

#endif
