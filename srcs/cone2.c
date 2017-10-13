/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:50:51 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 15:23:13 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect				normal_cone(t_cone *cone, t_vect p)
{
	t_vect	h;
	t_vect	v;
	t_vect	min;
	t_vect	add;

	normed(&cone->axis);
	min = min_vect(p, cone->summit);
	h = multiply_scalar(cone->axis, scalar_product(min, cone->axis));
	add = add_vect(cone->summit, h);
	v = min_vect(p, add);
	normed(&v);
	return (v);
}

float				cone_term_a(float expr, t_cone *cone, t_ray r)
{
	float res;

	res = pow(alpha_cone(expr, cone->axis.x, r.direction.x), 2) + \
	pow(alpha_cone(expr, cone->axis.y, r.direction.y), 2) + \
	pow(alpha_cone(expr, cone->axis.z, r.direction.z), 2) - \
	pow(alpha2cone(expr, cone->axis.x, cone->angle), 2) - \
	pow(alpha2cone(expr, cone->axis.y, cone->angle), 2) - \
	pow(alpha2cone(expr, cone->axis.z, cone->angle), 2);
	return (res);
}

float				cone_term_b(float expr, float expr2, t_cone *cone, t_ray r)
{
	float res;

	res = term(alpha_cone(expr, cone->axis.x, r.direction.x), \
			beta_cone(expr2, cone->axis.x, r.origin.x, cone->summit.x)) +\
		term(alpha_cone(expr, cone->axis.y, r.direction.y),  \
				beta_cone(expr2, cone->axis.y, r.origin.y, cone->summit.y)) + \
		term(alpha_cone(expr, cone->axis.z, r.direction.z),  \
				beta_cone(expr2, cone->axis.z, r.origin.z, cone->summit.z)) - \
		term(alpha2cone(expr, cone->axis.x, cone->angle), \
				beta2cone(expr2, cone->axis.x, cone->angle)) - \
		term(alpha2cone(expr, cone->axis.y, cone->angle), \
				beta2cone(expr2, cone->axis.y, cone->angle)) - \
		term(alpha2cone(expr, cone->axis.z, cone->angle), \
				beta2cone(expr2, cone->axis.z, cone->angle));
	return (res);
}

float				cone_term_c(float expr2, t_cone *cone, t_ray r)
{
	float res;

	res = pow(beta_cone(expr2, cone->axis.x, r.origin.x, cone->summit.x), 2) + \
	pow(beta_cone(expr2, cone->axis.y, r.origin.y, cone->summit.y), 2) + \
	pow(beta_cone(expr2, cone->axis.z, r.origin.z, cone->summit.z), 2) - \
	pow(beta2cone(expr2, cone->axis.x, cone->angle), 2) - \
	pow(beta2cone(expr2, cone->axis.y, cone->angle), 2) - \
	pow(beta2cone(expr2, cone->axis.z, cone->angle), 2);
	return (res);
}

t_hit_point			hit_cone(void *o, t_ray r)
{
	t_cone		*cone;
	float		expr;
	float		expr2;

	cone = (t_cone *)o;
	normed(&cone->axis);
	expr = cone->axis.x * r.direction.x + cone->axis.y * r.direction.y + \
		cone->axis.z * r.direction.z;
	expr2 = (r.origin.x - cone->summit.x) * cone->axis.x + (r.origin.y - \
			cone->summit.y) * cone->axis.y +\
			(r.origin.z - cone->summit.z) * cone->axis.z;
	return (resolution_cone(cone, r, expr, expr2));
}
