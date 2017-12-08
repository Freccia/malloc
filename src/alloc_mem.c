/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:05:10 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/08 19:11:39 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_meta	*mmap_zone_tiny()
{
	t_meta	*mem;

	if (!g_mem.tiny)
	{
		if ((g_mem.tiny = (t_meta*)mmap(0, TINY_ZONE, PROT, MAP, -1, 0))
				== MAP_FAILED)
			return (NULL);
		g_mem.tiny->size = TINY_ZONE - META_SIZE;
		return (g_mem.tiny);
	}
	if ((mem = (t_meta*)mmap(0, TINY_ZONE, PROT, MAP, -1, 0)) == MAP_FAILED)
			return (NULL);
	mem->size = TINY_ZONE - META_SIZE;
	return (mem);
}

static t_meta	*mmap_zone_small()
{
	t_meta	*mem;

	if (!g_mem.small)
	{
		if ((g_mem.small = (t_meta*)mmap(0, SMALL_ZONE, PROT, MAP, -1, 0))
				== MAP_FAILED)
			return (NULL);
		g_mem.small->size = SMALL_ZONE - META_SIZE;
		return (g_mem.small);
	}
	if ((mem = (t_meta*)mmap(0, SMALL_ZONE, PROT, MAP, -1, 0)) == MAP_FAILED)
			return (NULL);
	mem->size = SMALL_ZONE - META_SIZE;
	return (mem);
}

void			*alloc_mem_tiny(size_t size)
{
	t_meta	*mem;

	if ((mem = find_free_chunk(g_mem.tiny, size + META_SIZE)) == NULL)
	{
		mem = mmap_zone_tiny();
		update_meta_info(&mem, size);
		update_last_chunk(&(g_mem.tiny_last), mem);
		return (mem->data);	
	}
	update_meta_info(&mem, size);
	update_last_chunk(&(g_mem.tiny_last), mem);
	return (mem->data);
}

void			*alloc_mem_small(size_t size)
{
	t_meta	*mem;

	if ((mem = find_free_chunk(g_mem.small, size + META_SIZE)) == NULL)
	{
		mem = mmap_zone_small();
		update_meta_info(&mem, size);
		update_last_chunk(&(g_mem.small_last), mem);
		return (mem->data);	
	}
	update_meta_info(&mem, size);
	update_last_chunk(&(g_mem.small_last), mem);
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
		update_last_chunk(&(g_mem.large_last), mem);
		return (mem->data);
	}
	if ((mem = (t_meta*)mmap(0, size, PROT, MAP, -1, 0)) == MAP_FAILED)
		return (NULL);
	mem->next = NULL;
	mem->free = 0;
	mem->size = size;
	mem->data = mem + 1;
	update_last_chunk(&(g_mem.large_last), mem);
	if (g_mem.large == NULL)
		g_mem.large = mem;
	return (mem->data);
}
