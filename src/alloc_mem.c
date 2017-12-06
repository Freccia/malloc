/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:05:10 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/06 11:43:46 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta		*mmap_zone_tiny()
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

t_meta		*mmap_zone_small()
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

void		*alloc_mem_tiny(size_t size)
{
	t_meta	*mem;

	ft_putendl("HELLO TINY");
	if ((mem = find_free_chunk(g_mem.tiny, size + META_SIZE)) != NULL)
	{
		update_meta_info(&mem, size);
		update_last_chunk(&(g_mem.tiny_last), mem);
		ft_putendl("BYE TINY1");
		return (mem->data);	
	}
	mem = mmap_zone_tiny();
	update_meta_info(&mem, size);
	update_last_chunk(&(g_mem.tiny_last), mem);
	ft_putendl("BYE TINY2");
	return (mem->data);
}

void		*alloc_mem_small(size_t size)
{
	t_meta	*mem;

	ft_putendl("HELLO SMALL");
	if ((mem = find_free_chunk(g_mem.small, size + META_SIZE)) != NULL)
	{
		update_meta_info(&mem, size);
		update_last_chunk(&(g_mem.small_last), mem);
		ft_putendl("BYE SMALL");
		return (mem->data);	
	}
	mem = mmap_zone_small();
	update_meta_info(&mem, size);
	update_last_chunk(&(g_mem.small_last), mem);
	ft_putendl("BYE SMALL");
	return (mem->data);
}

void		*alloc_mem_large(size_t size)
{
	t_meta	*mem;

	ft_putendl("HELLO LARGE");
	if ((mem = find_free_chunk(g_mem.large, size)) != NULL)
	{
		mem->next = NULL;
		mem->free = 0;
		mem->size = size;
		mem->data = mem + META_SIZE;
		update_last_chunk(&(g_mem.large_last), mem);
		ft_putendl("BYE LARGE");
		return (mem->data);
	}
	if ((mem = (t_meta*)mmap(0, size, PROT, MAP, -1, 0)) == MAP_FAILED)
		return (NULL);
	update_last_chunk(&(g_mem.large_last), mem);
	if (g_mem.large == NULL)
		g_mem.large = mem;
	ft_putendl("BYE LARGE");
	return (mem->data);
}
