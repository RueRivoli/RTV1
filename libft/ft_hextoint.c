/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 13:54:46 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/27 12:45:27 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		convert_hex(char c)
{
	if (c > 47 && c < 58)
		return (c - 48);
	if (c > 64 && c < 71)
		return (c - 55);
	if (c > 96 && c < 103)
		return (c - 87);
	return (-1);
}

int		ft_hextoint(char *str)
{
	int		len;
	int		pow;
	int		res;

	res = 0;
	pow = 1;
	len = ft_strlen(str);
	while (len-- > 0)
	{
		if (convert_hex(str[len]) == -1)
			return (-1);
		res = res + pow * convert_hex(str[len]);
		pow = pow * 16;
	}
	return (res);
}
