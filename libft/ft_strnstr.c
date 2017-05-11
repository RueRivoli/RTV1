/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 20:23:21 by fgallois          #+#    #+#             */
/*   Updated: 2017/01/12 18:54:06 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_search(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && big[i + j]
					&& little[j] && i + j < len)
			{
				if (j == ft_strlen(little) - 1)
					return ((char*)big + i);
				j++;
			}
		}
		i++;
		j = 0;
	}
	return (NULL);
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (!ft_strlen(little))
		return ((char*)big);
	else
	{
		return (ft_search(big, little, len));
	}
}
