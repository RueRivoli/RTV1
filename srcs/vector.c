/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:52:01 by fgallois          #+#    #+#             */
/*   Updated: 2017/05/16 10:52:03 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect  *new_vect(float x, float y, float z)
{
    t_vect  *new;
    if (!(new = (t_vect*)malloc(sizeof(t_vect))))
        return (NULL);
    new->x = x;
    new->y = y;
    new->z = z;
    return (new);
}

float       scalar_product(t_vect *v1, t_vect *v2)
{
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vect *add_vect(t_vect *v1, t_vect *v2)
{
    return new_vect(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

t_vect *minus_vect(t_vect *v1, t_vect *v2)
{
    return (new_vect(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z));
}

float       norm(t_vect *v)
{
    return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

int     colin(t_vect *v, t_vect *w)
{
    if (v->x * w->y == v->y * w->x && v->y * w->z == v->z * w->y && v->x * w->z == v->z * w->x)
        return (1);  
    return (0);
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

t_vect  *product_vect(t_vect *u, t_vect *v)
{
    return (new_vect(u->y * v->z - u->z * v->y, u->z * v->x - u->x * v->z, u->x * v->y - u->y * v->x));
}

float       min(float r, float s)
{
    if (r < s)
        return (r);
    else 
        return (s);
}

float       max(float r, float s)
{
    if (r < s)
        return (s);
    else 
        return (r);
}

float       min_positiv(float r, float s)
{
    if (r < s && r > 0)
        return (r);
    else if (s > 0)
        return (s);
    else
        return (r);
}
