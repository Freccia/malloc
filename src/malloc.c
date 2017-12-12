/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:41:30 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/12 14:00:24 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void	*mem;

	pthread_mutex_lock(&g_mutex);
	if (size <= 0)
	{
		pthread_mutex_unlock(&g_mutex);
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
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&g_mutex);
	return (mem);
}
