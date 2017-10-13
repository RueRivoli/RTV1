/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:50:51 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 19:54:57 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_hit_point			resolution_cone(t_cone *cone, t_ray r, \
		float expr, float expr2)
{
	t_vect			v;
	t_hit_point		hp;
	float			res;
	float			delta;

	delta = pow(cone_term_b(expr, expr2, cone, r), 2) - 4.0 * \
			cone_term_a(expr, cone, r) * cone_term_c(expr2, cone, r);
	if (delta >= 0.0)
	{
		res = min_positiv_s((-cone_term_b(expr, expr2, cone, r) -\
					sqrt(delta)) / (2 * cone_term_a(expr, cone, r)),\
				(-cone_term_b(expr, expr2, cone, r) + sqrt(delta)) / (2 * \
					cone_term_a(expr, cone, r)), 0);
		if (res >= 0)
		{
			v = new_vect(r.origin.x + res * r.direction.x, r.origin.y + res * \
					r.direction.y, r.origin.z + res * r.direction.z);
			hp = new_hit_point(v, INFINI, normal_cone(cone, v), 4);
			return (hp);
		}
	}
	return (hp_null());
}
