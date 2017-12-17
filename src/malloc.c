/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:23:53 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/17 01:46:29 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*malloc(size_t size)
{
	t_meta	*mem;
	
	if (size = 0)
		return (NULL);
	if (size <= TINY_SIZE)
		mem = alloc_mem_tiny(size);
	else if (size <= SMALL_SIZE)
		mem = alloc_mem_small(size);
	else
		mem = alloc_mem_large(size);
	return (mem);
}
