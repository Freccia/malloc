/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 21:09:10 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/08 22:07:14 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t		print_memory(t_meta *list, char *str)
{
	size_t		tot;

	tot = 0;
	if (list)
	{
		ft_putstr(str);
		ft_putptr(list);
		ft_putchar('\n');
	}
	while (list)
	{
		if (list->free == 0)
		{
			ft_putptr(list->data);
			ft_putstr(" - ");
			ft_putptr((void*)list->data + list->size);
			ft_putstr(" : ");
			ft_putnbr(list->size);
			ft_putstr(" octets");
			ft_putstr(" : ");
			ft_putnbr(list->free);
			ft_putstr(" : ");
			ft_putptr(list->next);
			ft_putstr("\n");
			tot += list->size;
		}
		list = list->next;
	}
	return (tot);
}

void		show_alloc_mem(void)
{
	size_t		tot;

	tot = 0;
	tot += print_memory(g_mem.tiny, "TINY: ");
	tot += print_memory(g_mem.small, "SMALL: ");
	tot += print_memory(g_mem.large, "LARGE: ");
	ft_putstr("total: ");
	ft_putnbr(tot);
	ft_putendl(" octets");
}
