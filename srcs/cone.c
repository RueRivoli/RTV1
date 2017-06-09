/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:50:51 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/09 11:50:52 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cone      *new_cone(t_vect *summit, t_vect *axis, float angle)
{
	t_cone      *c;

	if (!(c = (t_cone *)malloc(sizeof(t_cone))))
		return (NULL);
	c->summit = summit;
	c->axis = axis; 
	c->angle = angle;
	return (c);
}

float       alpha_cone(float expr, float n, float dir)
{
	return (n * expr - dir);
}

float       beta_cone(float expr2, float n, float a, float o)
{
	return (n * expr2 + o - a);
}

float       alpha2cone(float expr, float n, float angle)
{
	return (expr * n * tan(angle));
}

float       beta2cone(float expr2, float n, float angle)
{
	return (expr2 * n * tan(angle));
}


t_vect              *normal_cone(t_cone *cone, t_vect *p)
{
	t_vect *h;
	t_vect *v;
	t_vect *norm;
	t_vect *min;
	t_vect *add;
	norm = normed_vect(cone->axis);
	min = minus_vect(p, cone->summit);
	h = multiply_scalar(norm, scalar_product(min, norm));
	add = add_vect(cone->summit, h);
	v = minus_vect(p, add);
	v = normed_vect(v);
	free(h);
	free(add);
	free(min);
	return (v);
}

t_hit_point         *hit_cone(void *o, t_ray *r)
{
	float a;
	float b;
	float c;
	float expr;
	float expr2;
	float delta;
	t_cone *cone;
	cone = (t_cone *)o;
	t_vect *v;
	float res;
	//t_vect *traj;

	cone->axis = normed_vect(cone->axis);
	expr = cone->axis->x * r->direction->x + cone->axis->y * r->direction->y + cone->axis->z * r->direction->z;
	expr2 = (r->origin->x - cone->summit->x) * cone->axis->x + (r->origin->y - cone->summit->y) * cone->axis->y +\
			(r->origin->z - cone->summit->z) * cone->axis->z;
	a =  pow(alpha_cone(expr, cone->axis->x, r->direction->x), 2) + pow(alpha_cone(expr, cone->axis->y, r->direction->y), 2)  +\
		 pow(alpha_cone(expr, cone->axis->z, r->direction->z), 2) - pow(alpha2cone(expr, cone->axis->x, cone->angle), 2) - pow(alpha2cone(expr, cone->axis->y, cone->angle), 2) - \
		 pow(alpha2cone(expr, cone->axis->z, cone->angle), 2);
	b = term(alpha_cone(expr, cone->axis->x, r->direction->x), beta_cone(expr2, cone->axis->x, r->origin->x, cone->summit->x)) +\
		term(alpha_cone(expr, cone->axis->y, r->direction->y),  beta_cone(expr2, cone->axis->y, r->origin->y, cone->summit->y))  +\
		term(alpha_cone(expr, cone->axis->z, r->direction->z),  beta_cone(expr2, cone->axis->z, r->origin->z, cone->summit->z)) - \
		term(alpha2cone(expr, cone->axis->x, cone->angle), beta2cone(expr2, cone->axis->x, cone->angle)) - term(alpha2cone(expr, cone->axis->y, cone->angle), beta2cone(expr2, cone->axis->y, cone->angle)) - \
		term(alpha2cone(expr, cone->axis->z, cone->angle), beta2cone(expr2, cone->axis->z, cone->angle));
	c = pow(beta_cone(expr2, cone->axis->x, r->origin->x, cone->summit->x), 2) +\
		pow(beta_cone(expr2, cone->axis->y, r->origin->y, cone->summit->y), 2)+\
		pow(beta_cone(expr2, cone->axis->z, r->origin->z, cone->summit->z), 2) - pow(beta2cone(expr2, cone->axis->x, cone->angle), 2) -\
		pow(beta2cone(expr2, cone->axis->y, cone->angle), 2) - pow(beta2cone(expr2, cone->axis->z, cone->angle), 2);
	delta = pow(b, 2) - 4.0 * a * c;
	if (delta >= 0.0)
	{
		//res = min((- b - sqrt(delta)) / (2 * a), (- b + sqrt(delta)) / (2 * a));
		res = min_positiv_s((- b - sqrt(delta)) / (2 * a), (- b + sqrt(delta)) / (2 * a), 0);
		//traj = multiply_scalar(r->direction, res);
		if (res >= 0 /**/ /*&& norm(traj) >= r->dist_to_screen*/)
		{
			v = new_vect(r->origin->x + res * r->direction->x, r->origin->y + res * r->direction->y, r->origin->z + res * r->direction->z);
			return (new_hit_point(v, INFINI, normal_cone(cone, v), 4));
		}
	}
	return (NULL);
}
