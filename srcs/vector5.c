/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:52:01 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 18:44:50 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					equals_hp(t_hit_point h1, t_hit_point h2)
{
	if (equals_vect(h1.vect, h2.vect) && h1.distance_to_cam == \
			h2.distance_to_cam && equals_vect(h1.normal, h2.normal) && \
			h1.form == h2.form)
		return (1);
	else
		return (0);
}

t_vect				add_vect_float(t_vect v, float f, int n)
{
	if (n == 1)
		v.x += f;
	else if (n == 2)
		v.y += f;
	else if (n == 3)
		v.z += f;
	return (v);
}

t_vect				add_vect_rotation(t_vect v, float theta, int n)
{
	float mem;

	if (n == 1)
	{
		mem = v.y;
		v.y = cos(theta) * v.y + sin(theta) * v.z;
		v.z = -sin(theta) * mem + cos(theta) * v.z;
	}
	else if (n == 2)
	{
		mem = v.y;
		v.x = cos(theta) * v.x + sin(theta) * v.z;
		v.z = -sin(theta) * mem + cos(theta) * v.z;
	}
	else if (n == 3)
	{
		mem = v.z;
		v.x = cos(theta) * v.x + sin(theta) * v.y;
		v.y = -sin(theta) * mem + cos(theta) * v.y;
	}
	normed(&v);
	return (v);
}

t_hit_point			hp_null(void)
{
	t_hit_point hp;

	hp.vect = vect_null();
	hp.distance_to_cam = 0.0;
	hp.normal = vect_null();
	hp.form = 0;
	return (hp);
}

int					equals_vect(t_vect v1, t_vect v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (1);
	else
		return (0);
}
