/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:52:01 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 18:40:46 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				rotation_vect_z(t_vect v, float angle)
{
	float	mem;

	mem = v.x;
	v.x = cos(angle * M_PI / 180) * v.x + sin(angle * M_PI / 180) * v.y;
	v.y = -sin(angle * M_PI / 180) * mem + cos(angle * M_PI / 180) * v.y;
}

void				rotation_vect_x(t_vect v, float angle)
{
	float	mem;

	mem = v.y;
	v.y = cos(angle * M_PI / 180) * v.y + sin(angle * M_PI / 180) * v.z;
	v.z = -sin(angle * M_PI / 180) * mem + cos(angle * M_PI / 180) * v.z;
}

void				find_angle(t_env *env, t_ray ray)
{
	t_vect		v;
	float		theta;
	float		add_phi;
	float		add_theta;
	float		n;

	n = norm(&ray.direction);
	add_phi = env->cam->add_phi;
	add_theta = env->cam->add_theta;
	v = multiply_scalar(ray.direction, -1);
	theta = asin((v.x) / (n * sin(acos(v.y / n))));
	ray.direction.x = n * sin(acos(v.y / n) + (add_phi * M_PI / 180)) * \
	sin(theta + (add_theta * M_PI / 180));
	ray.direction.y = n * cos(acos(v.y / n) + (add_phi * M_PI / 180));
	ray.direction.z = n * sin(acos(v.y / n) + (add_phi * M_PI / 180)) * \
					cos(theta + (add_theta * M_PI / 180));
	ray.direction = new_vect(-ray.direction.x, -ray.direction.y, \
			ray.direction.z);
}

t_vect				vect_null(void)
{
	t_vect		v;

	v.x = 0.0;
	v.y = 0.0;
	v.z = 0.0;
	return (v);
}

t_vect				vect_col(t_env *env)
{
	t_light		*light;
	t_vect		v;

	light = env->light;
	v.x = 0.2 * light->red;
	v.y = 0.2 * light->green;
	v.z = 0.2 * light->blue;
	return (v);
}
