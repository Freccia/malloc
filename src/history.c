/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 16:20:59 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/12 16:51:20 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		add_allocation_in_history(uint8_t type, size_t size)
{
	static t_alloc	*last = NULL;
	t_alloc			*ptr;

	if (!g_history)
	{
		if ((g_history = (t_alloc*)mmap(0, TINY_ZONE, PROT, MAP, -1, 0))
				== MAP_FAILED)
			return ;
		g_history->next = NULL;
		g_history->type = type;
		g_history->size = size;
		g_history->space_left = TINY_ZONE - sizeof(t_alloc);
		last = g_history;
		return ;
	}
	if (last->space_left - sizeof(t_alloc) <= 0)
	{
		if ((ptr = (t_alloc*)mmap(0, TINY_ZONE, PROT, MAP, -1, 0))
				== MAP_FAILED)
			return ;
		last->next = ptr;
		ptr->next = NULL;
		ptr->type = type;
		ptr->size = size;
		ptr->space_left = TINY_ZONE - sizeof(t_alloc);
		last = ptr;
		return ;
	}
	ptr = last + 1;
	ptr->next = NULL;
	ptr->type = type;
	ptr->size = size;
	ptr->space_left = last->space_left - sizeof(t_alloc);
}

static void	print_allocation_type(t_alloc *ptr)
{
	if (ptr->type == TYPE_MALLOC)
	{
		ft_putstr("malloc -- SIZE: ");
		ft_putnbr(ptr->size);
		ft_putchar('\n');
	}
	if (ptr->type == TYPE_MALLOC)
	{
		ft_putstr("calloc -- SIZE: ");
		ft_putnbr(ptr->size);
		ft_putchar('\n');
	}
	if (ptr->type == TYPE_MALLOC)
	{
		ft_putstr("realloc -- SIZE: ");
		ft_putnbr(ptr->size);
		ft_putchar('\n');
	}
	if (ptr->type == TYPE_MALLOC)
	{
		ft_putendl("free");
	}
}

void		print_allocation_history()
{
	t_alloc		*ptr;

	if (g_history)
	{
		ptr = g_history;
		while (ptr)
		{
			ft_putstr("TYPE: ");
			print_allocation_type(ptr);	
			ft_putchar('\n');
			ptr = ptr->next;
		}
	}
}
