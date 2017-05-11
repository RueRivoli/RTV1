/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 21:31:03 by fgallois          #+#    #+#             */
/*   Updated: 2017/01/11 16:35:39 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int i;
	int p;

	if (s != NULL && f != NULL)
	{
		i = 0;
		p = ft_strlen(s);
		while (i < p)
		{
			(*f)(i, s);
			i++;
			s++;
		}
	}
}
