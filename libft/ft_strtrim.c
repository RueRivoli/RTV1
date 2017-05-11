/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 12:30:11 by fgallois          #+#    #+#             */
/*   Updated: 2017/01/11 14:14:49 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*st;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 0)
		return ((char*)s);
	j = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
	}
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && j > i)
	{
		j--;
	}
	st = ft_strsub(s, i, j - i + 1);
	return (st);
}
