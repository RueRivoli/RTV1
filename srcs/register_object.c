/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:51:15 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 17:37:10 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "object.h"

int			register_sphere(char *line, t_env *env, int fd)
{
	t_vect		vect;
	float		rad;
	t_mater		*mat;
	t_sphere	*sp;

	mat = NULL;
	vect = read_origin(line, fd, "origin");
	if (!(rad = read_float(line, fd, "radius")))
		return (0);
	if (!(mat = read_mater(line, fd, "color")))
		return (0);
	sp = new_sphere(vect, rad);
	modify((void*)sp, line, fd, 1);
	env->obj = add_obj(env->obj, 1, mat, (void*)sp);
	return (1);
}

int			register_plan(char *line, t_env *env, int fd)
{
	t_vect		vect;
	t_vect		norm;
	t_mater		*mat;
	t_plan		*p;

	vect = read_origin(line, fd, "origin");
	norm = read_origin(line, fd, "normal");
	if (equals_vect(norm, vect_null()))
		return (0);
	if (!(mat = read_mater(line, fd, "color")))
		return (0);
	p = new_plan(vect, norm);
	modify((void*)p, line, fd, 2);
	env->obj = add_obj(env->obj, 2, mat, (void*)p);
	return (1);
}

int			register_cylinder(char *line, t_env *env, int fd)
{
	t_vect		vect;
	t_vect		norm;
	t_mater		*mat;
	t_cylinder	*cyl;
	float		rad;

	vect = read_origin(line, fd, "origin");
	norm = read_origin(line, fd, "normal");
	if (equals_vect(norm, vect_null()))
		return (0);
	if (!(rad = read_float(line, fd, "radius")))
		return (0);
	if (!(mat = read_mater(line, fd, "color")))
		return (0);
	cyl = new_cylinder(vect, norm, rad);
	modify((void*)cyl, line, fd, 3);
	env->obj = add_obj(env->obj, 3, mat, (void*)cyl);
	return (1);
}

int			register_cone(char *line, t_env *env, int fd)
{
	t_vect		vect;
	t_vect		axis;
	float		angle;
	t_mater		*mat;
	t_cone		*cone;

	vect = read_origin(line, fd, "summit");
	if (equals_vect(vect, vect_null()))
		return (0);
	axis = read_origin(line, fd, "axis");
	if (equals_vect(axis, vect_null()))
		return (0);
	if (!(angle = read_float(line, fd, "angle")))
		return (0);
	if (!(mat = read_mater(line, fd, "color")))
		return (0);
	cone = new_cone(vect, axis, angle);
	modify((void*)cone, line, fd, 4);
	cone->angle = cone->angle * M_PI / 180;
	env->obj = add_obj(env->obj, 4, mat, (void*)cone);
	return (1);
}

int			registering(int to, char *line, t_env *env, int fd)
{
	if (to == 1)
		return (register_sphere(line, env, fd));
	if (to == 2)
		return (register_plan(line, env, fd));
	if (to == 3)
		return (register_cylinder(line, env, fd));
	if (to == 4)
		return (register_cone(line, env, fd));
	return (0);
}
