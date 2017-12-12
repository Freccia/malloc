/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memalign.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 21:12:40 by lfabbro           #+#    #+#             */
/*   Updated: 2017/12/12 16:12:31 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <errno.h>

/*
**	(align & -align != align) :: To verify (align % 2 == 0)
*/

void		*memalign(size_t align, size_t size)
{
	void	*mem;
	void	*amem;

	if ((align & -align) != align)
	{
		errno = EINVAL;
		return (NULL);
	}
	if (size > SIZE_MAX - align)
	{
		errno = ENOMEM;
		return (NULL);
	}
	if ((mem = malloc(size + align - 1)) == NULL)
		return (NULL);
	amem = (void*)(((uintptr_t)mem + align - 1) & -align);
	return (amem);
}
