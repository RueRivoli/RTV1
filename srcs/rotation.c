/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 14:30:46 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 18:27:22 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			rotate_vector(t_env *env, t_vect *ray_dir)
{
	float		plus_phi;
	float		plus_theta;

	plus_phi = env->cam->add_phi;
	plus_theta = env->cam->add_theta;
	change_vect(ray_dir, plus_phi, plus_theta);
}

void			apply_trans(int to, void *o, float f, int n)
{
	t_sphere	*sp;
	t_plan		*p;
	t_cylinder	*cyl;
	t_cone		*c;

	if (to == 1)
	{
		sp = (t_sphere*)o;
		sp->origin = add_vect_float(sp->origin, f, n);
	}
	if (to == 2)
	{
		p = (t_plan*)o;
		p->origin = add_vect_float(p->origin, f, n);
	}
	if (to == 3)
	{
		cyl = (t_cylinder*)o;
		cyl->origin = add_vect_float(cyl->origin, f, n);
	}
	if (to == 4)
	{
		c = (t_cone*)o;
		c->summit = add_vect_float(c->summit, f, n);
	}
}

void			apply_rotate(int to, void *o, float f, int n)
{
	t_plan		*p;
	t_cylinder	*cyl;
	t_cone		*c;

	if (to == 2)
	{
		p = (t_plan*)o;
		p->normal = add_vect_rotation(p->normal, f, n);
	}
	if (to == 3)
	{
		cyl = (t_cylinder*)o;
		cyl->normal = add_vect_rotation(cyl->normal, f, n);
	}
	if (to == 4)
	{
		c = (t_cone*)o;
		c->axis = add_vect_rotation(c->axis, f, n);
	}
}
