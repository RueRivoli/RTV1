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

float           cylinder_term_a(float expr, t_cylinder *cyl, t_ray r)
{
    float res;
    res = pow(alpha_cylinder(expr, cyl->normal->x, r.direction.x), 2) + \
        pow(alpha_cylinder(expr, cyl->normal->y, r.direction.y), 2) +\
		 pow(alpha_cylinder(expr, cyl->normal->z, r.direction.z), 2);
    return (res);
}

float           cylinder_term_b(float expr, float expr2, t_cylinder *cyl, t_ray r)
{
    float res;

     res = term(alpha_cylinder(expr, cyl->normal->x, r.direction.x), \
     beta_cylinder(expr2, cyl->normal->x, r.origin.x, cyl->origin->x))+\
		term(alpha_cylinder(expr, cyl->normal->y, r.direction.y), \
        beta_cylinder(expr2, cyl->normal->y, r.origin.y, cyl->origin->y))+\
		term(alpha_cylinder(expr, cyl->normal->z, r.direction.z), \
        beta_cylinder(expr2, cyl->normal->z, r.origin.z, cyl->origin->z));
        return (res);
}

float           cylinder_term_c(float expr2, t_cylinder *cyl, t_ray r)
{
    float res;
    res = pow(beta_cylinder(expr2, cyl->normal->x, r.origin.x, cyl->origin->x), 2) +\
		pow(beta_cylinder(expr2, cyl->normal->y, r.origin.y, cyl->origin->y), 2) +\
		pow(beta_cylinder(expr2, cyl->normal->z, r.origin.z, cyl->origin->z), 2) - \
        pow(cyl->radius, 2);
    return (res);
}

t_hit_point         inter_colin(t_cylinder *cyl, t_ray r)
{
    t_vect w;
    t_hit_point hp;
    float oh;
    float oa;

    w = min_vect(r.origin, *cyl->origin);
	oh = scalar_product(w, *cyl->normal);
	oa = norm(w);
	//free(w);

	if (sqrt(pow(oa, 2) - pow(oh, 2)) <= cyl->radius)
	{
		hp = new_hit_point(new_vect (INFINI - 1, INFINI - 1, INFINI - 1), -1.0, new_vect(0,0,0), 3);
		return (hp);
	}
    return (NULL);
}

t_hit_point         hit_cylinder(void *o, t_ray r)
{
    t_cylinder *cyl;
    t_hit_point hp;
	float expr;
	float expr2;
	float delta;
	//t_vect *traj;
	float res;

	cyl = (t_cylinder*)o;
	expr = cyl->normal->x * r.direction.x + cyl->normal->y * r.direction.y + cyl->normal->z * r.direction.z;
	expr2 = (r.origin.x - cyl->origin->x) * cyl->normal->x + (r.origin.y - cyl->origin->y) * cyl->normal->y +\
			(r.origin.z - cyl->origin->z) * cyl->normal->z;

	delta = pow(cylinder_term_b(expr, expr2, cyl, r), 2) - 4 * cylinder_term_a(expr, cyl, r) * cylinder_term_c(expr2, cyl, r);
	if (colin(r.direction, *cyl->normal) == 1)
        return (inter_colin(cyl, r));
	else if (delta >= 0.0)
	{
		//res = max((- b - sqrt(delta)) / (2 * a), (- b + sqrt(delta)) / (2 * a));

		res = min_positiv_s((- cylinder_term_b(expr, expr2, cyl, r) - sqrt(delta)) / (2 * cylinder_term_a(expr, cyl, r)), (- cylinder_term_b(expr, expr2, cyl, r) + sqrt(delta)) / (2 * cylinder_term_a(expr, cyl, r)), 0);
		//traj = multiply_scalar(r->direction, res);
		if (res > 0 /*&& norm(traj) >= r->dist_to_screen*/)
		{
			hp = new_hit_point(new_vect(r.origin.x + res * r.direction.x, r.origin.y + res * r.direction.y, r.origin.z + res * r.direction.z), INFINI, \
            normal_cylinder(cyl, new_vect(r.origin.x + res * r.direction.x, r.origin.y + res * r.direction.y, r.origin.z + res * r.direction.z)),\
             3);
			return (hp);
		}
		else 
			return (NULL);
	}
	return (NULL);
}
