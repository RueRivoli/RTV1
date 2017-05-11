/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 21:03:36 by fgallois          #+#    #+#             */
/*   Updated: 2017/01/11 16:47:57 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		b;

	i = 0;
	b = 0;
	if (n == 0)
		return (0);
	else
	{
		while (*s1 == *s2 && *s1 != '\0' && i < n)
		{
			s1++;
			s2++;
			i++;
		}
	}
	if (i == n)
		return (0);
	else
		return (*(unsigned char*)s1 - *(unsigned char*)s2);
}
