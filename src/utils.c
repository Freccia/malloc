/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 14:44:34 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/17 16:44:44 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	join_free_chunks_list(t_chunk **list, t_chunk **last)
{
	t_chunk *next;
	t_chunk *ptr;

	if ((ptr = *list) == NULL)
		return ;
	while (ptr->next)
	{
		next = ptr->next;
		if (ptr->free && next && next->free)
		{
			ptr->size = ptr->size + next->size + META_SIZE;
			ptr->next = next->next;
		}
		else
			ptr = next;
	}
	*last = ptr;
}

void		join_free_chunks(void)
{
	join_free_chunks_list(&(g_mem.tiny), &(g_mem.tiny_last));
	join_free_chunks_list(&(g_mem.small), &(g_mem.small_last));
	join_free_chunks_list(&(g_mem.large), &(g_mem.large_last));
}

void			_init_memory_chunk(t_chunk **mem, size_t size, size_t zone_size)
{
	t_chunk	*ptr;
	t_chunk	*next;

	ptr = *mem;
	ptr->next = (t_chunk*)((char*)ptr + META_SIZE + size);
	ptr->size = size;
	ptr->free = 0;
	ptr->data = (char*)ptr + META_SIZE;
	next = ptr->next;
	next->next = NULL;
	next->size = zone_size - size - (META_SIZE * 2);
	next->free = 1;
	next->data = (char*)next + META_SIZE;
}

void			_update_meta_info(t_chunk **mem, size_t size)
{
	t_chunk	*ptr;
	t_chunk	*tmp;
	t_chunk	*next;

	ptr = *mem;
	next = ptr->next ? ptr->next : NULL;
	if (ptr->size > size + META_SIZE)
	{
		tmp = (t_chunk*)((char*)ptr + META_SIZE + size);
		tmp->next = next;
		tmp->size = ptr->size - META_SIZE - size;
		tmp->free = 1;
		tmp->data = (char*)tmp + META_SIZE;
		ptr->next = tmp;
		ptr->size = size;
	}
	ptr->free = 0;
}
