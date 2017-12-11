/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:07:31 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/11 16:09:17 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*resize_allocation(t_meta *ptr, size_t size)
{
	void	*mem;
	t_meta	*next;

	next = ptr->next ? ptr->next : NULL;
	if (next && next->free && (ptr->size + next->size + META_SIZE) >= size)
	{
		ptr->size = ptr->size + next->size + META_SIZE;
		ptr->free = 0;
		ptr->next = next->next;	
		return ((void*)ptr);
	}
	if ((mem = malloc(size)) == NULL)
		return (NULL);
	ft_memmove(mem, ptr->data, ptr->size);
	free(ptr);
	return (mem);
}

static void		*ft_realloc(void *ptr, size_t size)
{
	t_meta	*real_ptr;

	if (ptr == NULL)
	{
		return (malloc(size));
	}
	if ((real_ptr = find_memory_chunk(ptr)) == NULL)
	{
		return (malloc(size));
	}
	if ((ptr != NULL && size == 0) || real_ptr->size > size)
	{
		real_ptr->free = 1;
		return (malloc(size));
	}
	join_free_chunks();
	return(resize_allocation(real_ptr, size));
}

void		*realloc(void *ptr, size_t size)
{
	t_meta	*ptr_re;

	pthread_mutex_lock(&g_mutex);
	ptr_re = ft_realloc(ptr, size);
	pthread_mutex_lock(&g_mutex);
	return (ptr_re);
}
