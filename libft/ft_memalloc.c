/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 18:43:53 by fgallois          #+#    #+#             */
/*   Updated: 2017/03/03 15:23:53 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void *esp;

	if (size == 0 || !size)
		return (NULL);
	size += 1;
	if (!(esp = (void *)malloc(sizeof(void*) * size)))
		return (NULL);
	ft_bzero(esp, size);
	return (esp);
}
