/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:51:54 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 17:42:29 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_sphere		*new_sphere(t_vect v1, float rad)
{
	t_sphere *v;

	if (!(v = (t_sphere*)malloc(sizeof(t_sphere))))
		return (NULL);
	v->origin = v1;
	v->radius = rad;
	return (v);
}

t_vect			normal_sphere(t_sphere *sp, t_vect p)
{
	t_vect	min;

	min = min_vect(p, sp->origin);
	normed(&min);
	return (min);
}

t_hit_point		hit_sphere(void *o, t_ray r)
{
	t_sphere		*sp;
	t_vect			t;
	t_hit_point		hp;
	float			delta;
	float			b;
	float			c;
	float			res;

	sp = (void *)o;
	b = 2 * ((r.origin.x - sp->origin.x) * r.direction.x + (r.origin.y - \
				sp->origin.y) * r.direction.y + (r.origin.z - sp->origin.z) * \
			r.direction.z);
	c = pow(r.origin.x - sp->origin.x, 2) + pow(r.origin.y - sp->origin.y, \
			2) + pow(r.origin.z - sp->origin.z, 2) - pow(sp->radius, 2);
	delta = pow(b, 2) - 4 * 1.0 * c;
	if (delta >= 0.0)
	{
		res = min_positiv((-b - sqrt(delta)) / (2 * 1.0), (-b + \
					sqrt(delta)) / (2 * 1.0));
		if (res > 0.0)
		{
			t = new_vect(r.origin.x + res * r.direction.x, \
					r.origin.y + res * r.direction.y, r.origin.z + res * \
					r.direction.z);
			hp = new_hit_point(new_vect(r.origin.x + res * r.direction.x, \
						r.origin.y + res * r.direction.y, r.origin.z + \
						res * r.direction.z), \
					INFINI, normal_sphere(sp, t), 1);
			return (hp);
		}
	}
	return (hp_null());
}
