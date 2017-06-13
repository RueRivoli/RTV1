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

t_vect    *vect_central(t_env *env)
{
	t_vect *dir;
	t_vect *min;

	dir = center_average(env);
	min = minus_vect(dir, env->cam->pos);
	free(dir);
	normed(min);
	return (min);
}

t_vect         *vect_basic()
{
	t_vect *inter;
	t_vect *eye_center;
	t_vect *pix_center;

	eye_center = new_vect(600.0, 450.0, -100.0);
	pix_center = new_vect(600.0, 450.0, 0.0);
	inter = minus_vect(pix_center, eye_center);
	free(eye_center);
	free(pix_center);
	normed(inter);
	return (inter);
}

void    change_vect(t_vect *v, float phi1, float theta1)
{
	float phi0;
	float theta0;
	float x;
	float y;
	float z;
	phi0 = phi(v);
	theta0 = theta(v);
	y = norm(v) * cos(phi0 + phi1);
	x = norm(v) * sin(phi0 + phi1) * sin(theta1 + theta0);
	z = norm(v) * sin(phi0 + phi1) * cos(theta1 + theta0);
    v->y= y;
    v->x = x;
    v->z = z;
	//return (new_vect(x, y, z));
}       

float      phi(t_vect *v)
{
	return (acos(v->y / norm(v)));
}

float      theta(t_vect *v)
{
	float phi0;
	phi0 = phi(v);
	return (asin(v->x / (norm(v) * sin(phi0))));
}



