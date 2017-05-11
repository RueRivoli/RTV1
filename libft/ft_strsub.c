/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 19:31:26 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/28 14:26:16 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	i = 0;
	p = ft_strnew(len);
	if (p == NULL || s == NULL || start > ft_strlen(s)
			|| start + len > ft_strlen(s))
		return (NULL);
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	return (p);
}
