/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:36:20 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/17 01:59:26 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define _PROT			PROT_READ | PROT_WRITE
# define _MAP			MAP_PRIVATE | MAP_ANONYMOUS

# define PAGE_SIZE		getpagesize()
# define META_SIZE		sizeof(t_meta)

# define TINY_SIZE		PAGE_SIZE * 2
# define SMALL_SIZE		PAGE_SIZE * 16

# define TINY_ZONE		(TINY_SIZE + META_SIZE) * 100
# define SMALL_ZONE		(SMALL_SIZE + META_SIZE) * 100

typedef struct s_meta		t_meta;
typedef struct s_page		t_page;

struct	s_meta
{
	t_meta		*next;
	size_t		size;
	uint8_t		free;
	void		*data;
};

struct	t_page
{
	t_meta		*tiny;
	t_meta		*small;
	t_meta		*large;
	t_meta		*tiny_last;
	t_meta		*small_last;
	t_meta		*large_last;
};

t_page			*g_mem;

void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			free(size_t size);
void			show_alloc_mem(void);

#endif
