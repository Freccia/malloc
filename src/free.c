/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:14:42 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/06 19:41:17 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta		*find_ptr_in_list(t_meta *list, t_meta *list_last, void *ptr)
{
	t_meta	*tmp;

	if (list_last && list_last->data <= ptr && ptr < (void*)list_last->next)
		return (list_last);
	tmp = list;
	while (tmp && !(tmp->data <= ptr && ptr < (void*)tmp->next))
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_meta		*find_memory_chunk(void *ptr)
{
	t_meta	*tmp;

	if ((tmp = find_ptr_in_list(g_mem.tiny, g_mem.tiny_last, ptr)) != NULL)
		return (tmp);
	if ((tmp = find_ptr_in_list(g_mem.small, g_mem.small_last, ptr)) != NULL)
		return (tmp);
	if ((tmp = find_ptr_in_list(g_mem.large, g_mem.large_last, ptr)) != NULL)
		return (tmp);
	return (NULL);
}

void		ft_free(void *ptr)
{
	t_meta 	*real_ptr;

	if (!ptr)
		return ;
	real_ptr = find_memory_chunk(ptr);	
	if (real_ptr)
		real_ptr->free = 1;
}
