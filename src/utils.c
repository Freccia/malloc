/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:26:12 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/04 21:55:28 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta		*find_free_chunk(t_meta *mem, size_t size)
{
	t_meta	*ptr;

	ptr = mem;
	while (ptr && !ptr->free && ptr->size < size)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void		update_last_chunk(t_meta **last, t_meta *mem)
{
	if (!*last)
		*last = mem;
	else
	{
		(*last)->next = mem;
		*last = mem;
	}
}

void		update_meta_info(t_meta **mem, size_t chunk_size)
{
	t_meta	*ptr;
	t_meta	*ptr2;
	t_meta	*next;
	
	ptr = *mem;
	next = ptr->next ? ptr->next : NULL;
	ptr->free = 0;
	ptr->data = mem + META_SIZE; // (mem + 1)
	ptr->next = (void*)ptr + chunk_size;
	ptr2 = ptr->next;
	ptr2->size = ptr->size - chunk_size - META_SIZE;
	ptr->size = chunk_size;
	ptr2->free = 1;
	ptr2->data = ptr2 + META_SIZE;
	ptr2->next = next;
}
