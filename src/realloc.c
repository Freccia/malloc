/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:07:31 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/08 18:40:30 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*resize_allocation(t_meta *ptr, size_t size)
{
	t_meta	*tmp;
	t_meta	*next;

	next = ptr->next ? ptr->next : NULL;
	if (next && next->free && (ptr->size + next->size + META_SIZE) >= size)
	{
		ptr->size = ptr->size + next->size + META_SIZE;
		ptr->free = 0;
		ptr->next = next->next;	
		return ((void*)ptr);
	}
	tmp = ptr;
	if ((ptr = malloc(size)) == NULL)
		return (NULL);
	memcpy(ptr->data, tmp->data, tmp->size);
	free(tmp);
	return (ptr);
}

void		*ft_realloc(void *ptr, size_t size)
{
	t_meta	*old;

	ft_putstr("REALLOC! ");
	if (ptr == NULL)
		return (malloc(size));
	if ((old = find_memory_chunk(ptr)) == NULL)
		return (malloc(size));
	old = old->next;
	if ((ptr != NULL && size == 0) || old->size > size)
	{
		old->free = 1;
		return (malloc(size));
	}
	join_free_chunks();
	return(resize_allocation(old, size));
}
