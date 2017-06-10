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

t_vect  *new_vect(float x, float y, float z)
{
	t_vect  *new;
	if (!(new = (t_vect*)malloc(sizeof(t_vect))))
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}

float       scalar_product(t_vect *v1, t_vect *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vect *add_vect(t_vect *v1, t_vect *v2)
{
	return new_vect(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

t_vect *minus_vect(t_vect *v1, t_vect *v2)
{
	return (new_vect(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z));
}

float       norm(t_vect *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

int     colin(t_vect *v, t_vect *w)
{
	if (v->x * w->y == v->y * w->x && v->y * w->z == v->z * w->y && v->x * w->z == v->z * w->x)
		return (1);  
	return (0);
}

void        normed(t_vect *v)
{
    float nor;
    nor = norm(v);
    v->x = v->x / nor;
    v->y = v->y / nor;
    v->z = v->z / nor;
}
t_vect      *normed_vect(t_vect *v1)
{
	float nor;
	nor = norm(v1);
	return (new_vect(v1->x / (float)nor, v1->y / (float)nor, v1->z / (float)nor));
}

float   distance(t_vect *v1, t_vect *v2)
{
	return (sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2) + pow(v1->z - v2->z, 2)));
}

t_vect      *multiply_scalar(t_vect *v, float k)
{
	return (new_vect(k * v->x, k * v->y, k * v->z));
}

t_vect  *product_vect(t_vect *u, t_vect *v)
{
	return (new_vect(u->y * v->z - u->z * v->y, u->z * v->x - u->x * v->z, u->x * v->y - u->y * v->x));
}

float       min(float r, float s)
{
	if (r < s)
		return (r);
	else 
		return (s);
}

float       max(float r, float s)
{
	if (r < s)
		return (s);
	else 
		return (r);
}

float       min_positiv(float r, float s)
{
	if (r < s && r > 0)
		return (r);
	else if (s > 0)
		return (s);
	else
		return (r);
}

float       min_positiv_s(float r, float s, float seuil)
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

void    rotation_z(t_vect *v, float angle)
{
	float mem;
	mem = v->x;
	v->x = cos(angle * M_PI / 180) * v->x + sin(angle * M_PI / 180) * v->y;
	v->y = -sin(angle * M_PI / 180) * mem + cos(angle * M_PI / 180) * v->y;
}

void    rotation_x(t_vect *v, float angle)
{
	float mem;
	mem = v->y;
	v->y = cos(angle * M_PI / 180) * v->y + sin(angle * M_PI / 180) * v->z;
	v->z = -sin(angle * M_PI / 180) * mem + cos(angle * M_PI / 180) * v->z;
}

void    find_angle(t_env *env, t_ray *ray)
{
	float phi;
	float theta;
	t_vect *v;
	float add_phi;
	float add_theta;
	float n;
	n = norm(ray->direction);
	add_phi = env->cam->add_phi;
	add_theta = env->cam->add_theta;
	//printf("add_PHI %f\n", add_phi);
	//printf("add_THETA %f\n", add_theta);
	v = multiply_scalar(ray->direction, -1);
	phi = acos(v->y / n);
	free(v);
	//theta = acos((v->z)/(n * sin(phi)));
	theta = asin((v->x)/(n * sin(phi)));
	ray->direction->x = n * sin(phi + (add_phi * M_PI / 180)) * sin(theta + (add_theta * M_PI / 180));
	ray->direction->y = n * cos(phi + (add_phi * M_PI / 180));
	ray->direction->z = n * sin(phi + (add_phi * M_PI / 180)) * cos(theta + (add_theta * M_PI / 180));
	ray->direction = new_vect(- ray->direction->x, -ray->direction->y, ray->direction->z);
}
