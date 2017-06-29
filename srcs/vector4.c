/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:52:01 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/09 11:51:35 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void    rotation_z(t_vect v, float angle)
{
	float mem;
	mem = v.x;
	v.x = cos(angle * M_PI / 180) * v.x + sin(angle * M_PI / 180) * v.y;
	v.y = -sin(angle * M_PI / 180) * mem + cos(angle * M_PI / 180) * v.y;
}

void    rotation_x(t_vect v, float angle)
{
	float mem;
	mem = v.y;
	v.y = cos(angle * M_PI / 180) * v.y + sin(angle * M_PI / 180) * v.z;
	v.z = -sin(angle * M_PI / 180) * mem + cos(angle * M_PI / 180) * v.z;
}

void    find_angle(t_env *env, t_ray ray)
{
	float phi;
	float theta;
	t_vect v;
	float add_phi;
	float add_theta;
	float n;
	n = norm(ray.direction);
	add_phi = env->cam->add_phi;
	add_theta = env->cam->add_theta;
	//printf("add_PHI %f\n", add_phi);
	//printf("add_THETA %f\n", add_theta);
	v = multiply_scalar(ray.direction, -1);
	phi = acos(v.y / n);
	//free(v);
	//theta = acos((v->z)/(n * sin(phi)));
	theta = asin((v.x)/(n * sin(phi)));
	ray.direction.x = n * sin(phi + (add_phi * M_PI / 180)) * sin(theta + (add_theta * M_PI / 180));
	ray.direction.y = n * cos(phi + (add_phi * M_PI / 180));
	ray.direction.z = n * sin(phi + (add_phi * M_PI / 180)) * cos(theta + (add_theta * M_PI / 180));
	ray.direction = new_vect(-ray.direction.x, -ray.direction.y, ray.direction.z);
}

t_vect 		vect_null(void)
{
	t_vect v;
	v.x = 0.0;
	v.y = 0.0;
	v.z = 0.0;
	return (v);
}

t_hit_point 		hp_null(void)
{
	t_hit_point hp;
	hp.vect = vect_null();
	hp.distance_to_cam = 0.0;
	hp.normal = vect_null();
	hp.form = 0;
	return (hp);
}

int		equals_vect(t_vect v1, t_vect v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (1);
	else
		return (0);
}

int		equals_hp(t_hit_point h1, t_hit_point h2)
{
	if (equals_vect(h1.vect, h2.vect) && h1.distance_to_cam == h2.distance_to_cam && equals_vect(h1.normal, h2.normal) && h1.form == h2.form)
		return (1);
	else
		return (0);

}

