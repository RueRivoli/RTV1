/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 11:46:41 by fgallois          #+#    #+#             */
/*   Updated: 2017/05/16 11:46:43 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "object.h"

typedef struct s_sphere
{
    t_vect      *origin;
    float       radius;
}       t_sphere;     

typedef struct s_plan
{
    t_vect      *origin;
    t_vect      *normal;
}       t_plan;

typedef struct s_cylinder
{
    t_vect      *origin;
    t_vect      *normal;
    float       radius;
}       t_cylinder;

typedef struct s_cone
{
    t_vect *summit;
    t_vect  *axis;
    float   angle;
}       t_cone;

t_sphere    *new_sphere(t_vect *v1, float rad);
t_plan      *new_plan(t_vect *origin, t_vect *normal);
t_cylinder  *new_cylinder(t_vect *origin, t_vect *normal, float radius);
t_cone      *new_cone(t_vect *summit, t_vect *axis, float angle);

#endif
