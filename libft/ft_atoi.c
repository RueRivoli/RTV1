/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:54:48 by fgallois          #+#    #+#             */
/*   Updated: 2017/01/20 17:54:54 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int			ft_find(const char *str, int i)
{
	int ind;
	int j;
	int p;

	j = 0;
	p = 0;
	ind = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]) == 1)
	{
		ind = (int)(str[i]) - 48;
		i++;
		j = 10 * p + ind;
		p = j;
	}
	return (p);
}

int					ft_atoi(const char *str)
{
	int		i;
	int		p;
	int		sign;

	p = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]) == 1 && str[i] != '\0')
		i++;
	if ((str[i] == '+' || str[i] == '-') && ft_isdigit(str[i + 1]) == 1)
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (sign * ft_find(str, i));
}
