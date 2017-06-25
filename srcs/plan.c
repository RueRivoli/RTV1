/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:51:28 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/09 11:51:29 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_plan  	*new_plan(t_vect *origin, t_vect *normal)
{
	t_plan      *plan;

	if (!(plan = (t_plan *)malloc(sizeof(t_plan))))
		return (NULL);
	plan->origin = origin;
	plan->normal = normal;
	return (plan);
}

int         belong_to_plan(t_plan *p, t_vect *v)
{
	t_vect  *v1;
	v1 = minus_vect(v, p->origin);
	if (scalar_product(v1, p->normal) == 0.0)
	{
		free(v1);
		return (1);
	}
	free(v1);
	return (0);
}

t_hit_point			*hit_ortho(t_ray*r, t_plan *p, t_vect *min)
{
	if (scalar_product(min, p->normal) == 0.0)
	{
			free(min);
			return (new_hit_point(new_vect(r->origin->x, r->origin->y, r->origin->z), 0.0, normed_vect(p->normal), 2));
	}
	return (NULL);
}

t_hit_point         *hit_plan(void *o, t_ray *r)
{
	t_plan *p;
	t_vect *min;
	//t_vect *traj;
	float den;
	float res;

	p = (t_plan *)o;
	min = minus_vect(p->origin, r->origin);
	res = scalar_product(p->normal, min);
	den = scalar_product(p->normal, r->direction);
	if (den == 0.0)
		return (hit_ortho(r, p, min));
	else if (fabsf(den) > 1e-6)
	{
		res /= den;
		free(min);
		//traj = multiply_scalar(r->direction, res);
		if (res > 0.0)
			 return (new_hit_point(new_vect(r->origin->x + res * r->direction->x, r->origin->y + res * r->direction->y, r->origin->z + res * r->direction->z)\
			, 0.0, normed_vect(p->normal), 2));
	}
	else
		free(min);
	return (NULL);
}
