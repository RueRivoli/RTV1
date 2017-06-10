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

t_cylinder  *new_cylinder(t_vect *origin, t_vect *normal, float radius)
{
	t_cylinder      *cyl;

	if (!(cyl = (t_cylinder *)malloc(sizeof(t_cylinder))))
		return (NULL);
	cyl->origin = origin;
	cyl->normal = normed_vect(normal); 
	cyl->radius = radius;
	return (cyl);
}

int         belong_to_cylinder(t_cylinder *c, t_vect *v)
{
	t_vect  *v1;
	t_vect *norm;
	t_vect *p;
	t_vect *a;

	v1 = minus_vect(v, c->origin);
	norm = normed_vect(c->normal);
	p = multiply_scalar(norm , scalar_product(v, norm));
	free(v1);
	a = add_vect(c->origin, p);
	if (distance(v, a) <= c->radius)
	{
		free(p);
		free(norm);
		free(a);
		return (1);
	}
	free(p);
	free(norm);
	free(a);
	return (0);
}

float       alpha_cylinder(float expr, float n, float dir)
{
	return (n * expr - dir);
}

float       beta_cylinder(float expr2, float n, float a, float o)
{
	return (n * expr2 + o - a);
}

t_vect              *normal_cylinder(t_cylinder *cyl, t_vect *p)
{
	t_vect *h;
	t_vect *v;
	t_vect *n;
	t_vect *min;
	t_vect *ad;
	n = normed_vect(cyl->normal);
	p = minus_vect(p, cyl->origin);
	h = multiply_scalar(n , scalar_product(p, n));
	ad = add_vect(cyl->origin, h);
	min = minus_vect(p, ad);
	v = normed_vect(min);
	free(p);
	free(h);
	free(n);
	free(ad);
	free(min);
	return (v);
}
