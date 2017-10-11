/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:51:15 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 14:13:59 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		sum_sphere(t_sphere *sp, float *x, float *y, float *z)
{
	*x += sp->origin.x;
	*y += sp->origin.y;
	*z += sp->origin.z;
}

void		sum_plan(t_plan *p, float *x, float *y, float *z)
{
	*x += p->origin.x;
	*y += p->origin.y;
	*z += p->origin.z;
}

void		sum_cylinder(t_cylinder *cyl, float *x, float *y, float *z)
{
	*x += cyl->origin.x;
	*y += cyl->origin.y;
	*z += cyl->origin.z;
}

void		sum_cone(t_cone *c, float *x, float *y, float *z)
{
	*x += c->summit.x;
	*y += c->summit.y;
	*z += c->summit.z;
}

void		add_coord1(t_obj *obj, float *x, float *y, float *z)
{
	t_sphere	*sp;
	t_plan		*p;

	if (obj->form == 1)
	{
		sp = (t_sphere*)obj->type;
		sum_sphere(sp, x, y, z);
	}
	else if (obj->form == 2)
	{
		p = (t_plan*)obj->type;
		sum_plan(p, x, y, z);
	}
}
