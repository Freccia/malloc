/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:09:23 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/12 14:12:15 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_meta	*search_free_chunk(t_meta *mem, size_t size)
{
	t_meta	*ptr;

	ptr = mem;
	while (ptr)
	{
		if (ptr->free && ptr->size >= size)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

t_meta			*find_free_chunk(t_meta *mem, size_t size)
{
	t_meta	*ptr;

	if ((ptr = search_free_chunk(mem, size)) != NULL)
		return (ptr);
	join_free_chunks();
	if ((ptr = search_free_chunk(mem, size)) != NULL)
		return (ptr);
	return (NULL);
}

static t_meta	*search_ptr_in_list(t_meta *list, t_meta *list_last, void *ptr)
{
	t_meta	*tmp;

	if (list_last && list_last->data <= ptr &&
			ptr < (void*)list_last + list_last->size)
		return (list_last);
	tmp = list;
	while (tmp && !(tmp->data <= ptr && ptr < (void*)tmp + tmp->size))
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_meta			*find_memory_chunk(void *ptr)
{
	t_meta	*tmp;

	if ((tmp = search_ptr_in_list(g_mem.tiny, g_mem.tiny_last, ptr)) != NULL)
		return (tmp);
	if ((tmp = search_ptr_in_list(g_mem.small, g_mem.small_last, ptr)) != NULL)
		return (tmp);
	if ((tmp = search_ptr_in_list(g_mem.large, g_mem.large_last, ptr)) != NULL)
		return (tmp);
	return (NULL);
}
