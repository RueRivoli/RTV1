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

t_vect              *normal_cone(t_cone *cone, t_vect *p)
{
	t_vect *h;
	t_vect *v;
	t_vect *min;
	t_vect *add;
	normed(cone->axis);
	min = minus_vect(p, cone->summit);
	h = multiply_scalar(cone->axis, scalar_product(min, cone->axis));
	add = add_vect(cone->summit, h);
	v = minus_vect(p, add);
	normed(v);
	free(h);
	free(add);
	free(min);
	return (v);
}

float				cone_term_a(float expr, t_cone *cone, t_ray *r)
{
	float res;

	res = pow(alpha_cone(expr, cone->axis->x, r->direction->x), 2) + pow(alpha_cone(expr, cone->axis->y, r->direction->y), 2)  +\
		 pow(alpha_cone(expr, cone->axis->z, r->direction->z), 2) - pow(alpha2cone(expr, cone->axis->x, cone->angle), 2) - pow(alpha2cone(expr, cone->axis->y, cone->angle), 2) - \
		 pow(alpha2cone(expr, cone->axis->z, cone->angle), 2);
		 return (res);
}

float				cone_term_b(float expr, float expr2, t_cone *cone, t_ray *r)
{
	float res;

	res = term(alpha_cone(expr, cone->axis->x, r->direction->x), beta_cone(expr2, cone->axis->x, r->origin->x, cone->summit->x)) +\
		term(alpha_cone(expr, cone->axis->y, r->direction->y),  beta_cone(expr2, cone->axis->y, r->origin->y, cone->summit->y))  +\
		term(alpha_cone(expr, cone->axis->z, r->direction->z),  beta_cone(expr2, cone->axis->z, r->origin->z, cone->summit->z)) - \
		term(alpha2cone(expr, cone->axis->x, cone->angle), beta2cone(expr2, cone->axis->x, cone->angle)) - term(alpha2cone(expr, cone->axis->y, cone->angle), beta2cone(expr2, cone->axis->y, cone->angle)) - \
		term(alpha2cone(expr, cone->axis->z, cone->angle), beta2cone(expr2, cone->axis->z, cone->angle));
		return (res);
}


float				cone_term_c(float expr2, t_cone *cone, t_ray *r)
{
	float res;
	
	res = pow(beta_cone(expr2, cone->axis->x, r->origin->x, cone->summit->x), 2) +\
		pow(beta_cone(expr2, cone->axis->y, r->origin->y, cone->summit->y), 2)+\
		pow(beta_cone(expr2, cone->axis->z, r->origin->z, cone->summit->z), 2) - pow(beta2cone(expr2, cone->axis->x, cone->angle), 2) -\
		pow(beta2cone(expr2, cone->axis->y, cone->angle), 2) - pow(beta2cone(expr2, cone->axis->z, cone->angle), 2);
	return (res);
}

t_hit_point         *hit_cone(void *o, t_ray *r)
{
	t_cone *cone;
	t_vect *v;
	t_hit_point *hp;
	float expr;
	float expr2;
	float delta;
	float res;

	cone = (t_cone *)o;
	//t_vect *traj;
	normed(cone->axis);
	expr = cone->axis->x * r->direction->x + cone->axis->y * r->direction->y + cone->axis->z * r->direction->z;
	expr2 = (r->origin->x - cone->summit->x) * cone->axis->x + (r->origin->y - cone->summit->y) * cone->axis->y +\
			(r->origin->z - cone->summit->z) * cone->axis->z;
	delta = pow(cone_term_b(expr, expr2, cone, r), 2) - 4.0 * cone_term_a(expr, cone, r) * cone_term_c(expr2, cone, r);
	if (delta >= 0.0)
	{
		//res = min((- b - sqrt(delta)) / (2 * a), (- b + sqrt(delta)) / (2 * a));
		res = min_positiv_s((- cone_term_b(expr, expr2, cone, r) - sqrt(delta)) / (2 * cone_term_a(expr, cone, r)), (- cone_term_b(expr, expr2, cone, r) + sqrt(delta)) / (2 * cone_term_a(expr, cone, r)), 0);
		//traj = multiply_scalar(r->direction, res);
		if (res >= 0 /*&& norm(traj) >= r->dist_to_screen*/)
		{
			v = new_vect(r->origin->x + res * r->direction->x, r->origin->y + res * r->direction->y, r->origin->z + res * r->direction->z);
			hp = new_hit_point(v, INFINI, normal_cone(cone, v), 4);
			return (hp);
		}
	}
	return (NULL);
}
