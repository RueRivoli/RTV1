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
    return new_vect(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}

t_vect  *normed_vector(t_vect *v1)
{
    float norm;
    norm = sqrt(v1->x * v1->x + v1->y * v1->y + v1->z * v1->z);
    return new_vect(v1->x / norm, v1->y / norm, v1->z / norm);
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
