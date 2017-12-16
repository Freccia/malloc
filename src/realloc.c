/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:07:31 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/16 22:37:44 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*resize_allocation(t_meta *ptr, size_t size)
{
	void	*mem;
	t_meta	*tmp;
	t_meta	*next;
	size_t	tmp_size;

	next = ptr->next ? ptr->next : NULL;
	if (next && next->free && (ptr->size + next->size) > size)
	{
		//pthread_mutex_lock(&g_mutex);
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
		//pthread_mutex_unlock(&g_mutex);
		return ((void*)ptr->data);
	}
	if ((mem = malloc(size)) == NULL)
		return (NULL);
	//pthread_mutex_lock(&g_mutex);
	ft_memmove(mem, ptr->data, ptr->size);
	ptr->free = 1;
	//pthread_mutex_unlock(&g_mutex);
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
		//pthread_mutex_lock(&g_mutex);
		real_ptr->free = 1;
		//pthread_mutex_unlock(&g_mutex);
		return (malloc(size));
	}
	//pthread_mutex_lock(&g_mutex);
	join_free_chunks();
	//pthread_mutex_unlock(&g_mutex);
	return (resize_allocation(real_ptr, size));
}

void			*realloc(void *ptr, size_t size)
{
	void	*re_ptr;

	ft_putendl("HEL REALLOC");
	//pthread_mutex_lock(&g_mutex);
	add_allocation_in_history(TYPE_REALLOC, size, ptr);
	//pthread_mutex_unlock(&g_mutex);
	re_ptr = ft_realloc(ptr, size);
	ft_putendl("GDB REALLOC");
	return (re_ptr);
}
