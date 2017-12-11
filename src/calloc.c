/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:09:19 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/11 16:09:52 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	t_meta	*mem;
	size_t	tot_size;

	pthread_mutex_lock(&g_mutex);
	tot_size = count * size;
	if ((mem = malloc(tot_size)) == NULL)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	ft_memset(mem, 0, tot_size);
	pthread_mutex_unlock(&g_mutex);
	return (mem);
}
