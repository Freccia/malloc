/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:14:42 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/16 22:37:40 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	if (munmap(tmp->next, tmp->next->size) == -1)
**		ft_putendl_fd("Error: munmap failed [EINVAL]", 2);
*/

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
			munmap(tmp->next, tmp->next->size);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	ft_free(void *ptr)
{
	t_meta	*tmp;

	if (!ptr)
		return ;
	tmp = find_memory_chunk(ptr);
	if (tmp && tmp->size > SMALL_ZONE)
		unmap_large_zone(tmp);
	if (tmp)
		tmp->free = 1;
}

/*
**#ifdef DEBUG
**	print_free_chunks(g_mem.tiny, 0);
**	print_free_chunks(g_mem.small, 0);
**	print_free_chunks(g_mem.large, 0);
**#endif
*/

void		free(void *ptr)
{
	ft_putendl("HEL FREE");
	//pthread_mutex_lock(&g_mutex);
	add_allocation_in_history(TYPE_FREE, 0, ptr);
	ft_free(ptr);
	join_free_chunks();
	//pthread_mutex_unlock(&g_mutex);
	ft_putendl("GDB FREE");
}
