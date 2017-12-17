/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 14:44:34 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/17 16:59:31 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_chunk	*search_free_chunk(size_t size, t_chunk *list)
{
	t_chunk		*ptr;

	ptr = list;
	while (ptr)
	{
		if (ptr->free && ptr->size >= size)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

t_chunk			*find_free_chunk(size_t size, t_chunk *list)
{
	t_chunk		*ptr;

	if ((ptr = search_free_chunk(size, list)) != NULL)
		return (ptr);
	join_free_chunks();
	if ((ptr = search_free_chunk(size, list)) != NULL)
		return (ptr);
	return (NULL);
}

static t_chunk	*search_chunk_in_list(t_chunk *list, void *ptr)
{
	t_chunk	*tmp;

	tmp = list;
	while (tmp && !(tmp->data <= ptr && ptr < (void*)tmp->data + tmp->size))
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_chunk			*find_memory_chunk(void *ptr)
{
	t_chunk	*tmp;

	if ((tmp = search_chunk_in_list(g_mem.tiny, ptr)) != NULL)
		return (tmp);
	if ((tmp = search_chunk_in_list(g_mem.small, ptr)) != NULL)
		return (tmp);
	if ((tmp = search_chunk_in_list(g_mem.large, ptr)) != NULL)
		return (tmp);
	return (NULL);
}
