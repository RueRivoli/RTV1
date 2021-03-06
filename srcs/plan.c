/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:51:28 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 17:28:36 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_plan				*new_plan(t_vect origin, t_vect normal)
{
	t_plan		*plan;

	if (!(plan = (t_plan *)malloc(sizeof(t_plan))))
		return (NULL);
	plan->origin = origin;
	plan->normal = normal;
	return (plan);
}

t_hit_point			hit_ortho(t_ray r, t_plan *p, t_vect min)
{
	if (scalar_product(min, p->normal) == 0.0)
	{
		normed(&p->normal);
		return (new_hit_point(new_vect(r.origin.x, r.origin.y, \
						r.origin.z), 0.0, p->normal, 2));
	}
	return (hp_null());
}

t_hit_point			hit_plan(void *o, t_ray r)
{
	t_plan		*p;
	t_vect		min;
	float		den;
	float		res;

	p = (t_plan *)o;
	min = min_vect(p->origin, r.origin);
	res = scalar_product(p->normal, min);
	den = scalar_product(p->normal, r.direction);
	if (den == 0.0)
		return (hit_ortho(r, p, min));
	else if (fabsf(den) > 1e-6)
	{
		res /= den;
		normed(&p->normal);
		if (res > 0.0)
			return (new_hit_point(new_vect(r.origin.x + res * \
			r.direction.x, r.origin.y + res * r.direction.y, \
			r.origin.z + res * r.direction.z)\
			, 0.0, p->normal, 2));
	}
	return (hp_null());
}
