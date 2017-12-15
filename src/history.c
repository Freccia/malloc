/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 16:20:59 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/15 16:16:09 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*alloc_page_history(t_alloc **last, uint8_t type, \
				size_t size, void *location)
{
		t_alloc	*tmp;

		if ((tmp = (t_alloc*)mmap(0, TINY_ZONE, PROT, MAP, -1, 0))
				== MAP_FAILED)
			return (NULL);
		ft_memset(tmp, 0, TINY_ZONE);
		if (*last)
			(*last)->next = tmp;
		tmp->next = NULL;
		tmp->type = type;
		tmp->size = size;
		tmp->location = location;
		tmp->space_left = TINY_ZONE - sizeof(t_alloc);
		*last = tmp;
		return ((void*)tmp);
}

void				add_allocation_in_history(uint8_t type, size_t size, void *location)
{
	static t_alloc	*last = NULL;
	t_alloc			*ptr;

	if (!g_history)
	{
		g_history = alloc_page_history(&last, type, size, location);
		return ;
	}
	if (last->space_left - sizeof(t_alloc) <= 0)
	{
		alloc_page_history(&last, type, size, location);
		return ;
	}
	ptr = last + 1;
	ptr->next = NULL;
	ptr->type = type;
	ptr->size = size;
	ptr->location = location;
	ptr->space_left = last->space_left - sizeof(t_alloc);
	last->next = ptr;
	last = ptr;
}

static void	print_allocation_type(t_alloc *ptr)
{
	if (ptr->type == TYPE_MALLOC)
	{
		ft_putstr("malloc	 -- size: ");
		ft_putnbr(ptr->size);
	}
	if (ptr->type == TYPE_CALLOC)
	{
		ft_putstr("calloc   -- size: ");
		ft_putnbr(ptr->size);
	}
	if (ptr->type == TYPE_REALLOC)
	{
		ft_putstr("realloc  -- size: ");
		ft_putnbr(ptr->size);
	}
	if (ptr->type == TYPE_FREE)
	{
		ft_putstr("free     -- location: ");
		ft_putptr(ptr->location);
	}
}

void		print_allocation_history()
{
	t_alloc		*ptr;

	if (g_history)
	{
		ptr = g_history;
		ft_putendl("Memory Requests: ");
		while (ptr)
		{
			print_allocation_type(ptr);	
			ft_putchar('\n');
			ptr = ptr->next;
		}
	}
}
