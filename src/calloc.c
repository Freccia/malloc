/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:09:19 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/15 20:24:52 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	Multiplicate safely n * size, if it overflows returns a big number
**  that malloc will fail to allocate.
**	This is valid until we are working on a 64 machine.
*/

static size_t safe_mult_64(size_t n, size_t size)
{
	__uint128_t dn;
	__uint128_t dsize;
	__uint128_t drsize;

	dn = n;
	dsize = size;
	drsize = dn * dsize;
	if (drsize >> 64)
		return (~0ULL);
	return (drsize);
}

void	*calloc(size_t count, size_t size)
{
	t_meta	*mem;
	size_t	tot;

	tot = safe_mult_64(count, size);
	add_allocation_in_history(TYPE_CALLOC, tot, NULL);
	if ((mem = malloc(tot)) == NULL)
		return (NULL);
	ft_memset(mem, 0, tot);
	return (mem);
}
