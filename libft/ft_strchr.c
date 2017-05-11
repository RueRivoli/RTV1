/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 12:53:46 by fgallois          #+#    #+#             */
/*   Updated: 2017/01/10 14:05:33 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;
	size_t l;

	i = 0;
	l = ft_strlen(s) + 1;
	while (i < l)
	{
		if (*s == (unsigned char)c)
			return ((char*)s);
		i++;
		s++;
	}
	return (NULL);
}
