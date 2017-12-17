/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:46:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/17 16:38:06 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_chunk	*_mmap_alloc(size_t size, size_t zone_size,
		t_chunk **list, t_chunk **last)
{
	t_chunk	*mem;
	void	*tmp;

	if ((tmp = mmap(0, zone_size, _PROT, _MAP, -1, 0)) == MAP_FAILED)
	{
		ft_putendl("malloc(): unable to allocate memory");
		return (NULL);
	}
	mem = (t_chunk*)tmp;
	_init_memory_chunk(&mem, size, zone_size);
	if (!*list)
		*list = mem;
	if (*last)
		(*last)->next = mem;
	*last = mem;
	return (mem);
}

void			*alloc_mem_tiny(size_t size)
{
	t_chunk	*mem;

	if ((mem = find_free_chunk(size, g_mem.tiny)))
	{
		_update_meta_info(&mem, size);
		return (mem->data);
	}
	mem = _mmap_alloc(size, TINY_ZONE, &g_mem.tiny, &g_mem.tiny_last);
	return (mem->data);
}

void			*alloc_mem_small(size_t size)
{
	t_chunk	*mem;

	if ((mem = find_free_chunk(size, g_mem.small)))
	{
		_update_meta_info(&mem, size);
		return (mem->data);
	}
	mem = _mmap_alloc(size, SMALL_ZONE,  &g_mem.small, &g_mem.small_last);
	return (mem->data);
}

void			*alloc_mem_large(size_t size)
{
	void	*tmp;
	t_chunk	*mem;

	if ((tmp = mmap(0, size + META_SIZE, _PROT, _MAP, -1, 0)) == MAP_FAILED)
	{
		ft_putendl("malloc(): unable to allocate memory");
		return (NULL);
	}
	mem = (t_chunk*)tmp;
	mem->next = NULL;
	mem->size = size;
	mem->free = 0;
	mem->data = (char*)mem + META_SIZE;
	if (!g_mem.large)
		g_mem.large = mem;
	if (g_mem.large_last)
		g_mem.large_last->next = mem;
	g_mem.large_last = mem;
	return (mem->data);
}
