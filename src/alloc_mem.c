/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:46:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/17 01:59:55 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*mmap_alloc(size_t size, t_meta *list, t_meta *last)
{
	t_meta	*mem;

	if (list)
	{
		mem = mmap(0, TINY_ZONE, _PROT, _MAP, -1, 0);
	}
}

void		*alloc_mem_tiny(size_t size)
{
	t_meta	*mem;

	if ((mem = find_mem_chunk(size)))
		return (mem);
	mem = mmap_alloc(size, &g_mem.tiny, &g_mem.tiny_last);
	return (mem);
}

void		*alloc_mem_small(size_t size)
{
	t_meta	*mem;

	if ((mem = find_mem_chunk(size)))
		return (mem);
	mem = mmap_alloc(size, &g_mem.small, &g_mem.small_last);
	return (mem);
}

void		*alloc_mem_large(size_t size)
{
	t_meta	*mem;

	mem = mmap_alloc(size, &g_mem.large, &g_mem.large_last);
	return (mem);
}
