/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:52:01 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/09 11:51:35 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int     colin(t_vect *v, t_vect *w)
{
	if (v->x * w->y == v->y * w->x && v->y * w->z == v->z * w->y && v->x * w->z == v->z * w->x)
		return (1);  
	return (0);
}

void        normed(t_vect *v)
{
    float nor;
    nor = norm(v);
    v->x = v->x / nor;
    v->y = v->y / nor;
    v->z = v->z / nor;
}
t_vect      *normed_vect(t_vect *v1)
{
	float nor;
	nor = norm(v1);
	return (new_vect(v1->x / (float)nor, v1->y / (float)nor, v1->z / (float)nor));
}

float   distance(t_vect *v1, t_vect *v2)
{
	return (sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2) + pow(v1->z - v2->z, 2)));
}

t_vect      *multiply_scalar(t_vect *v, float k)
{
	return (new_vect(k * v->x, k * v->y, k * v->z));
}
