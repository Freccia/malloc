/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:36:35 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/06 19:15:21 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		put_hexa(unsigned long h)
{
	const char *hex = "0123456789abcdef";

	if (h >= 16)
	{
		put_hexa(h / 16);
		put_hexa(h % 16);
	}
	else
		ft_putchar(hex[h]);
}

void		put_pointer(void *ptr)
{
	ft_putstr("0x");
	put_hexa((unsigned long)ptr);
}

size_t		print_memory(t_meta *list, char *str)
{
	size_t		tot;

	tot = 0;
	if (list)
	{
		ft_putstr(str);
		put_pointer(list);
		ft_putchar('\n');
	}
	while (list)
	{
		if (list->free == 0)
		{
			put_pointer(list->data);
			ft_putstr(" - ");
			put_pointer((void*)list->data + list->size);
			ft_putstr(" : ");
			ft_putnbr(list->size);
			ft_putendl(" octets");
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
