/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:52:01 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 18:23:35 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		min(float r, float s)
{
	if (r < s)
		return (r);
	else
		return (s);
}

float		max(float r, float s)
{
	if (r < s)
		return (s);
	else
		return (r);
}

float		min_positiv(float r, float s)
{
	if (r < s && r > 0)
		return (r);
	else if (s > 0)
		return (s);
	else
		return (r);
}

float		min_positiv_s(float r, float s, float seuil)
{
	if (r <= s)
	{
		if (r >= seuil)
			return (r);
		else if (s >= seuil)
			return (s);
	}
	else if (s <= r)
	{
		if (s >= seuil)
			return (s);
		else if (r >= seuil)
			return (r);
	}
	else if (r > seuil && s > seuil)
		return (-1.0);
	return (-1.0);
}
