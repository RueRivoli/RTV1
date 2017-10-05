/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <fgallois@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:17:13 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/26 14:24:19 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

float	ft_atof(char *str)
{
	float	rez;
	float	fact;
	int		dot_seen;

	rez = 0;
	fact = 1;
	dot_seen = 0;
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		fact = *str == '-' ? (str++, -1) : (str++, 1);
	while ((ft_isdigit(*str) || *str == '.') && *str != '\0')
	{
		if (dot_seen == 0 && *str == '.')
			dot_seen = 1;
		else if (ft_isdigit(*str))
		{
			if (dot_seen)
				fact /= 10.0f;
			rez = rez * 10.0f + (float)(*str - '0');
		}
		str++;
	}
	return (rez * fact);
}