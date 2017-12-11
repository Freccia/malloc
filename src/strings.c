/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 19:24:38 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/11 21:23:48 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	find_and_print_strings(t_meta *mem, char *str)
{
	t_meta	*ptr;

	ptr = mem;
	while (ptr)
	{
		if 
	}
}

void		*print_strings()
{
	pthread_mutex_lock(&g_mutex);
	find_and_print_strings(g_mem.tiny, "TINY: ");
	find_and_print_strings(g_mem.small, "SMALL: ");
	find_and_print_strings(g_mem.large, "LARGE: ");
	pthread_mutex_unlock(&g_mutex);
}
