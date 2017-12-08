/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:26:12 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/08 22:17:51 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		init_first_chunk(t_meta **mem, size_t size)
{
	(*mem)->next = NULL;
	(*mem)->free = 1;
	(*mem)->size = size - META_SIZE; 
	(*mem)->data = (*mem) + META_SIZE;
}

void		update_meta_info(t_meta **mem, size_t chunk_size)
{
	t_meta	*ptr;
	t_meta	*ptr2;
	t_meta	*next;

	ptr = *mem;
	next = ptr->next ? ptr->next : NULL;
	ptr->free = 0;
	ptr->data = (void*)*mem + META_SIZE;
	if ((long)(ptr->size - chunk_size - META_SIZE) > (long)META_SIZE)
	{
		ptr->next = (void*)ptr + chunk_size + META_SIZE;
		ptr2 = ptr->next;
		ptr2->size = ptr->size - chunk_size - META_SIZE;
		ptr->size = chunk_size;
		ptr2->free = 1;
		ptr2->data = (void*)ptr2 + META_SIZE;
		ptr2->next = next;
	}
}
