/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 15:44:27 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/26 16:03:15 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		unmap_large_zone(t_chunk *ptr)
{
	t_chunk	*tmp;
	t_chunk *next;

	tmp = g_mem.large;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		if ((void*)tmp->next == ptr)
		{
			next = ptr->next;
			tmp->next = next;
			munmap(ptr, ptr->size);
			return ;
		}
		tmp = tmp->next;
	}
}

void			free(void *ptr)
{
	t_chunk	*real_ptr;

	if (ptr == NULL)
		return ;
	pthread_mutex_lock(&g_mutex);
	if ((real_ptr = find_memory_chunk(ptr)) == NULL)
		return ;
	if (real_ptr->size > SMALL_SIZE)
		unmap_large_zone(real_ptr);
	real_ptr->free = 1;
	pthread_mutex_unlock(&g_mutex);
}
