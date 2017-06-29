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

t_cone      *new_cone(t_vect summit, t_vect axis, float angle)
{
	t_cone      *c;

	if (!(c = (t_cone *)malloc(sizeof(t_cone))))
		return (NULL);
	c->summit = summit;
	c->axis = axis; 
	c->angle = angle;
	return (c);
}

float       alpha_cone(float expr, float n, float dir)
{
	return (n * expr - dir);
}

float       beta_cone(float expr2, float n, float a, float o)
{
	return (n * expr2 + o - a);
}

float       alpha2cone(float expr, float n, float angle)
{
	return (expr * n * tan(angle));
}

float       beta2cone(float expr2, float n, float angle)
{
	return (expr2 * n * tan(angle));
}
