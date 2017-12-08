/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:14:42 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/08 18:42:45 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	join_free_chunks_list(t_meta **list, t_meta **last)
{
	t_meta *next;
	t_meta *ptr;

	if ((ptr = *list) == NULL)
		return ;
	while (ptr->next)
	{
		next = ptr->next;
		if (ptr->free && next && next->free &&
				(ptr->size + next->size + META_SIZE < TINY_SIZE))
		{
			ptr->size = ptr->size + next->size + META_SIZE;
			ptr->next = next->next;
		}
		else
			ptr->next = next;
	}
	*last = ptr;
}

void		join_free_chunks()
{
	join_free_chunks_list(&(g_mem.tiny), &(g_mem.tiny_last));	
	join_free_chunks_list(&(g_mem.small), &(g_mem.small_last));	
	join_free_chunks_list(&(g_mem.large), &(g_mem.large_last));
}

static void	unmap_large_zone(void *ptr)
{
	t_meta	*tmp;

	tmp = g_mem.large;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		if ((void*)tmp->next == ptr)
		{
			tmp->next = tmp->next->next;
			if (munmap(tmp->next, tmp->next->size))
				ft_putendl_fd("Error: unmapping page failed.", 2);
			return ;
		}
		tmp = tmp->next;
	}
}

void		ft_free(void *ptr)
{
	t_meta 	*tmp;

	ft_putstr("FREE \n");
	if (!ptr)
		return ;
	tmp = find_memory_chunk(ptr);	
	if (tmp && tmp->size > SMALL_ZONE)
		unmap_large_zone(tmp);
	if (tmp)
		tmp->free = 1;
}
