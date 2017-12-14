/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:07:31 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/14 16:53:31 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// TODO fix realloc
static void		*resize_allocation(t_meta *ptr, size_t size)
{
	void	*mem;
	t_meta	*tmp;
	t_meta	*next;
	size_t	tmp_size;

	next = ptr->next ? ptr->next : NULL;
	if (next && next->free && (ptr->size + next->size) > size)
	{
		tmp_size = next->size;
		tmp = next->next;
		ptr->next = (void*)ptr->data + size;
		ptr->free = 0;
		next = ptr->next;
		next->size = tmp_size - (size - ptr->size);
		ptr->size = size;
		next->next = tmp;
		next->data = (void*)next + META_SIZE;
		next->free = 1;
		return ((void*)ptr);
	}
	if ((mem = malloc(size)) == NULL)
		return (NULL);
	ft_memmove(mem, ptr->data, ptr->size);
	ptr->free = 1;
	return (mem);
}

static void		*ft_realloc(void *ptr, size_t size)
{
	t_meta	*real_ptr;

	if (ptr == NULL)
	{
		return (malloc(size));
	}
	if ((real_ptr = find_memory_chunk(ptr)) == NULL ||
			(real_ptr && real_ptr->free))
	{
		return (NULL);
	}
	if ((ptr != NULL && size == 0) || real_ptr->size > size)
	{
		real_ptr->free = 1;
		return (malloc(size));
	}
	join_free_chunks();
	return (resize_allocation(real_ptr, size));
}

void			*realloc(void *ptr, size_t size)
{
	t_meta	*ptr_re;

	pthread_mutex_lock(&g_mutex);
	add_allocation_in_history(TYPE_REALLOC, size, ptr);
	ptr_re = ft_realloc(ptr, size);
	pthread_mutex_lock(&g_mutex);
	return (ptr_re);
}
