/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:26:12 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/12 14:14:59 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		print_free_chunks(t_meta *mem, size_t size)
{
	t_meta	*ptr;

	ptr = mem;
	ft_putstr("Looking for size >= ");
	ft_putnbr(size);
	ft_putendl(" ");
	while (ptr)
	{
		if (ptr->free)
		{
			ft_putstr("Found: ");
			ft_putnbr(ptr->size);
			ft_putendl(" ");
		}
		ptr = ptr->next;
	}
}

static void	join_free_chunks_list(t_meta **list, t_meta **last)
{
	t_meta *next;
	t_meta *ptr;

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
