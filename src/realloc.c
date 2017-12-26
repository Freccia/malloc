/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 16:18:08 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/26 16:03:39 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*resize_allocation(t_chunk *ptr, size_t size, t_chunk *next)
{
	void	*mem;
	t_chunk	*tmp;

	if (next && next->free && (ptr->size + next->size) > size)
	{
		tmp = next->next;
		ptr->next = (void*)ptr->data + size;
		ptr->free = 0;
		next = ptr->next;
		next->size = next->size - (size - ptr->size);
		ptr->size = size;
		next->next = tmp;
		next->data = (void*)next + META_SIZE;
		next->free = 1;
		return ((void*)ptr->data);
	}
	pthread_mutex_unlock(&g_mutex);
	if ((mem = malloc(size)) == NULL)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	ft_memmove(mem, ptr->data, ptr->size);
	ptr->free = 1;
	pthread_mutex_unlock(&g_mutex);
	return (mem);
}

void			*realloc(void *ptr, size_t size)
{
	t_chunk	*real_ptr;

	if (ptr == NULL)
	{
		return (malloc(size));
	}
	pthread_mutex_lock(&g_mutex);
	if ((real_ptr = find_memory_chunk(ptr)) == NULL)
	{
		return (NULL);
	}
	if ((ptr != NULL && size == 0) || real_ptr->size > size)
	{
		real_ptr->free = 1;
		pthread_mutex_unlock(&g_mutex);
		return (malloc(size));
	}
	join_free_chunks();
	return (resize_allocation(real_ptr, size, real_ptr->next));
}
