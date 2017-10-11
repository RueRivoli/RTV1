/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:51:15 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 14:15:49 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		add_coord2(t_obj *obj, float *x, float *y, float *z)
{
	t_cylinder	*cyl;
	t_cone		*c;

	if (obj->form == 3)
	{
		cyl = (t_cylinder*)obj->type;
		sum_cylinder(cyl, x, y, z);
	}
	else if (obj->form == 4)
	{
		c = (t_cone*)obj->type;
		sum_cone(c, x, y, z);
	}
}

t_vect		center_average(t_env *env)
{
	t_obj		*obj;
	float		x;
	float		y;
	float		z;
	int			ct;

	obj = env->obj;
	ct = 0;
	x = 0.0;
	y = 0.0;
	z = 0.0;
	while (obj)
	{
		ct++;
		add_coord1(obj, &x, &y, &z);
		add_coord2(obj, &x, &y, &z);
		obj = obj->next;
	}
	return (new_vect(x / ct, y / ct, z / ct));
}
