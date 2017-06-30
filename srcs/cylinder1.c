/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:50:29 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/09 11:51:42 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cylinder  *new_cylinder(t_vect origin, t_vect normal, float radius)
{
	t_cylinder      *cyl;

	if (!(cyl = (t_cylinder *)malloc(sizeof(t_cylinder))))
		return (NULL);
	cyl->origin = origin;
	normed(&normal); 
	cyl->normal = normal;
	cyl->radius = radius;
	return (cyl);
}


float       alpha_cylinder(float expr, float n, float dir)
{
	return (n * expr - dir);
}

float       beta_cylinder(float expr2, float n, float a, float o)
{
	return (n * expr2 + o - a);
}

t_vect              normal_cylinder(t_cylinder *cyl, t_vect p)
{
	t_vect h;
	t_vect om;
	t_vect n;
	t_vect min;
	t_vect ad;

	n = vect_null();
	normed(&cyl->normal);
	om = min_vect(p, cyl->origin);
	h = multiply_scalar(n, scalar_product(om, n));
	ad = add_vect(cyl->origin, h);
	min = min_vect(p, ad);
	normed(&min);
	return (min);
}
