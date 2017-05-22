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

typedef struct s_hit_point
{
    t_vect  *vect;
    float   distance_to_cam;
}               t_hit_point;

typedef struct s_ray 
{   
    t_vect      *origin;
    t_vect      *direction;
    t_hit_point  *hit_point;
}               t_ray;

typedef struct s_mater
{
    float     alpha;
    int       ir;
    int       ig;
    int       ib;
}               t_mater;

typedef struct s_obj
{
  	t_hit_point		*(*is_hit)(void *ob, t_ray *r);
	void			*type;
	t_mater			*mater;
	struct s_obj			*next;
}               t_obj;


t_sphere    *new_sphere(t_vect *v1, float rad);
int         belong_to_sphere(t_sphere *sp, t_vect *v);
t_hit_point         *hit_sphere(void *o, t_ray *r);

t_plan      *new_plan(t_vect *origin, t_vect *normal);
int         belong_to_plan(t_plan *p, t_vect *v);
t_hit_point         *hit_plan(void *o, t_ray *r);



t_cylinder  *new_cylinder(t_vect *origin, t_vect *normal, float radius);
float       alpha_cylinder(float expr, float n, float dir);
float       beta_cylinder(float expr2, float n, float a, float o);
t_hit_point         *hit_cylinder(void *o, t_ray *r);

t_cone      *new_cone(t_vect *summit, t_vect *axis, float angle);
float       alpha_cone(float expr, float n, float dir);
float       beta_cone(float expr2, float n, float a, float o);
float       alpha2cone(float expr, float n, float angle);
float       beta2cone(float expr2, float n, float angle);
t_hit_point         *hit_cone(void *o, t_ray *r);

t_mater       *new_mater(float f, int r, int g, int b);

t_obj       *add_obj(t_obj *obj, int obj_type, t_mater *mater, void *type);

#endif
