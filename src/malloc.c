/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:41:30 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/06 18:32:59 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h> //norme

void	*ft_malloc(size_t size)
{
	void	*mem;
	
	if (size <= 0)
		return (NULL);
	else if (size <= TINY_SIZE)
		mem = alloc_mem_tiny(size);
	else if (size <= SMALL_SIZE)
		mem = alloc_mem_small(size);
	else
		mem = alloc_mem_large(size + META_SIZE);
	if (mem == MAP_FAILED)
		return (NULL);
	return (mem);
}
