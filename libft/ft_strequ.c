/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:28:43 by fgallois          #+#    #+#             */
/*   Updated: 2017/01/02 12:11:26 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (*s1 == *s2 & *s2 != '\0')
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (0);
	else
		return (1);
}
