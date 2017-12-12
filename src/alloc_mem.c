/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:05:10 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/12 13:58:46 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_meta	*mmap_zone(t_meta **g_zone, size_t zone_size)
{
	t_meta	*mem;

	if (!*g_zone)
	{
		if ((*g_zone = (t_meta*)mmap(0, zone_size, PROT, MAP, -1, 0))
				== MAP_FAILED)
			return (NULL);
		(*g_zone)->size = zone_size - META_SIZE;
		return (*g_zone);
	}
	if ((mem = (t_meta*)mmap(0, zone_size, PROT, MAP, -1, 0)) == MAP_FAILED)
		return (NULL);
	mem->size = zone_size - META_SIZE;
	return (mem);
}

void			*alloc_mem_tiny(size_t size)
{
	t_meta	*mem;

	if ((mem = find_free_chunk(g_mem.tiny, size + META_SIZE)) == NULL)
	{
		mem = mmap_zone(&(g_mem.tiny), TINY_ZONE);
		update_meta_info(&mem, size);
		if (g_mem.tiny_last)
			g_mem.tiny_last->next = mem;
		g_mem.tiny_last = mem;
		return (mem->data);
	}
	update_meta_info(&mem, size);
	g_mem.tiny_last = mem;
	return (mem->data);
}

void			*alloc_mem_small(size_t size)
{
	t_meta	*mem;

	if ((mem = find_free_chunk(g_mem.small, size + META_SIZE)) == NULL)
	{
		mem = mmap_zone(&(g_mem.small), SMALL_ZONE);
		update_meta_info(&mem, size);
		if (g_mem.small_last)
			g_mem.small_last->next = mem;
		g_mem.small_last = mem;
		return (mem->data);
	}
	update_meta_info(&mem, size);
	g_mem.small_last = mem;
	return (mem->data);
}

void			*alloc_mem_large(size_t size)
{
	t_meta	*mem;

	if ((mem = find_free_chunk(g_mem.large, size)) != NULL)
	{
		mem->next = NULL;
		mem->free = 0;
		mem->size = size;
		mem->data = mem + 1;
		g_mem.large_last = mem;
		return (mem->data);
	}
	if ((mem = (t_meta*)mmap(0, size, PROT, MAP, -1, 0)) == MAP_FAILED)
		return (NULL);
	mem->next = NULL;
	mem->free = 0;
	mem->size = size;
	mem->data = mem + 1;
	if (g_mem.large_last)
		g_mem.large_last->next = mem;
	g_mem.large_last = mem;
	if (g_mem.large == NULL)
		g_mem.large = mem;
	return (mem->data);
}
