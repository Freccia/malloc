/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:41:30 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/16 22:38:41 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_malloc(size_t size)
{
	void	*mem;

//	pthread_mutex_lock(&g_mutex);
	add_allocation_in_history(TYPE_MALLOC, size, NULL);
	if (size <= 0 || size >= SIZE_MAX)
	{
//		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	else if (size <= TINY_SIZE)
		mem = alloc_mem_tiny(size);
	else if (size <= SMALL_SIZE)
		mem = alloc_mem_small(size);
	else
		mem = alloc_mem_large(size + META_SIZE);
	if (mem == MAP_FAILED)
	{
//		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
//	pthread_mutex_unlock(&g_mutex);
	return (mem);
}

void		*malloc(size_t size)
{
	t_meta	*mem;

	if (!g_mem.tiny && !g_mem.small && !g_mem.large)
	{
		pthread_mutex_init(&g_mutex, NULL);
	}
	//pthread_mutex_lock(&g_mutex);
	mem = ft_malloc(size);
	//pthread_mutex_unlock(&g_mutex);
	return (mem);
}
