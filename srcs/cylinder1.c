/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:50:29 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 18:03:49 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cylinder		*new_cylinder(t_vect origin, t_vect normal, float radius)
{
	t_cylinder		*cyl;

	if (!(cyl = (t_cylinder *)malloc(sizeof(t_cylinder))))
		return (NULL);
	cyl->origin = origin;
	normed(&normal);
	cyl->normal = normal;
	cyl->radius = radius;
	return (cyl);
}

float			alpha_cylinder(float expr, float n, float dir)
{
	return (n * expr - dir);
}

float			beta_cylinder(float expr2, float n, float a, float o)
{
	return (n * expr2 + o - a);
}

t_vect			normal_cylinder(t_cylinder *cyl, t_vect p)
{
	t_vect h;
	t_vect om;
	t_vect min;
	t_vect ad;

	normed(&cyl->normal);
	om = min_vect(p, cyl->origin);
	h = multiply_scalar(cyl->normal, scalar_product(om, cyl->normal));
	ad = add_vect(cyl->origin, h);
	min = min_vect(p, ad);
	normed(&min);
	return (min);
}

t_hit_point		resolution_cyl(t_cylinder *cyl, t_ray r, float expr, \
		float expr2)
{
	t_hit_point		hp;
	float			res;
	float			delta;

	delta = pow(cylinder_term_b(expr, expr2, cyl, r), 2) - 4 * \
			cylinder_term_a(expr, cyl, r) * cylinder_term_c(expr2, cyl, r);
	if (delta >= 0.0)
	{
		res = min_positiv_s((-cylinder_term_b(expr, expr2, cyl, r) - \
					sqrt(delta)) / (2 * cylinder_term_a(expr, cyl, r)), \
				(-cylinder_term_b(expr, expr2, cyl, r) + sqrt(delta)) / (2 * \
					cylinder_term_a(expr, cyl, r)), 0);
		if (res > 0)
		{
			hp = new_hit_point(new_vect(r.origin.x + res * r.direction.x, \
						r.origin.y + res * r.direction.y, r.origin.z + res * \
						r.direction.z), INFINI, \
					normal_cylinder(cyl, new_vect(r.origin.x + res * \
							r.direction.x, r.origin.y + res * r.direction.y, \
							r.origin.z + res * r.direction.z)),\
					3);
			return (hp);
		}
	}
	return (hp_null());
}
