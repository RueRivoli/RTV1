/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:07:00 by fgallois          #+#    #+#             */
/*   Updated: 2017/01/11 16:46:16 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*t;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	t = ft_strnew(ft_strlen(s));
	if (!t)
		return (NULL);
	i = 0;
	while (s[i])
	{
		t[i] = f(s[i]);
		i++;
	}
	t[i] = '\0';
	return (t);
}
