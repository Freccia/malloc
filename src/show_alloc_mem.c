/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 21:09:10 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/12 14:04:54 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	print_memory_ex(t_meta *list, char *str, size_t tot)
{
	if (list && str)
	{
		ft_putstr(str);
		ft_putptr(list);
		ft_putchar('\n');
	}
	while (list)
	{
		if (list->free >= 0)
		{
			ft_putptr(list->data);
			ft_putstr(" - ");
			ft_putptr((void*)list->data + list->size);
			ft_putstr(" : ");
			ft_putnbr(list->size);
			ft_putendl(" octets");
			ft_putendl("Data: ");
			ft_print_memory(list->data, list->size);
			ft_putchar('\n');
			tot += list->size;
		}
		list = list->next;
	}
	return (tot);
}

static size_t	print_memory(t_meta *list, char *str)
{
	size_t		tot;

	tot = 0;
	if (list && str)
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
			ft_putendl(" octets");
			tot += list->size;
		}
		list = list->next;
	}
	return (tot);
}

void			show_alloc_mem(void)
{
	size_t		tot;

	pthread_mutex_lock(&g_mutex);
	tot = 0;
	tot += print_memory(g_mem.tiny, "TINY: ");
	tot += print_memory(g_mem.small, "SMALL: ");
	tot += print_memory(g_mem.large, "LARGE: ");
	ft_putstr("total: ");
	ft_putnbr(tot);
	ft_putendl(" octets");
	pthread_mutex_unlock(&g_mutex);
}

void			show_alloc_mem_ex(void)
{
	size_t		tot;

	pthread_mutex_lock(&g_mutex);
	tot = 0;
	tot += print_memory_ex(g_mem.tiny, "TINY: ", 0);
	tot += print_memory_ex(g_mem.small, "SMALL: ", 0);
	tot += print_memory_ex(g_mem.large, "LARGE: ", 0);
	ft_putstr("total: ");
	ft_putnbr(tot);
	ft_putendl(" octets");
	pthread_mutex_unlock(&g_mutex);
}
