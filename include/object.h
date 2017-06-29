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
    t_vect      origin;
    float       radius;
}       t_sphere;     

typedef struct s_plan
{
    t_vect      origin;
    t_vect      normal;
}       t_plan;

typedef struct s_cylinder
{
    t_vect      origin;
    t_vect    normal;
    float       radius;
}       t_cylinder;

typedef struct s_cone
{
    t_vect summit;
    t_vect  axis;
    float   angle;
}       t_cone;

typedef struct s_hit_point
{
    t_vect  vect;
    float   distance_to_cam;
    t_vect  normal;
    int     form;

}               t_hit_point;

typedef struct s_ray 
{   
    t_vect      origin;
    t_vect      direction;
    float       dist_to_screen;
    t_vect      color; 
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
  	t_hit_point		(*is_hit)(void *ob, t_ray r);
	void			*type;
    int             form;
	t_mater			*mater;
	struct s_obj			*next;
}               t_obj;

/*creation.c*/

t_mater                      *new_mater(float f, int r, int g, int b);
t_obj                        *add_obj(t_obj *obj, int obj_type, t_mater *mater, void *type);

/*cone1.c*/

t_cone                       *new_cone(t_vect summit, t_vect axis, float angle);
float                        alpha_cone(float expr, float n, float dir);
float                          beta_cone(float expr2, float n, float a, float o);
float                           alpha2cone(float expr, float n, float angle);
float                            beta2cone(float expr2, float n, float angle);

/*cone2.c*/

t_vect                       normal_cone(t_cone *cone, t_vect p);
float				        cone_term_a(float expr, t_cone *cone, t_ray r);
float				        cone_term_b(float expr, float expr2, t_cone *cone, t_ray r);
float				        cone_term_c(float expr2, t_cone *cone, t_ray r);
t_hit_point                  hit_cone(void *o, t_ray r);

/*cylinder1.c*/

t_cylinder                  *new_cylinder(t_vect origin, t_vect normal, float radius);
float                       alpha_cylinder(float expr, float n, float dir);
float                       beta_cylinder(float expr2, float n, float a, float o);
t_vect                      normal_cylinder(t_cylinder *cyl, t_vect p);


/*cylinder2.c*/


float                       cylinder_term_a(float expr, t_cylinder *cyl, t_ray r);
float                       cylinder_term_b(float expr, float expr2, t_cylinder *cyl, t_ray r);
float                       cylinder_term_c(float expr2, t_cylinder *cyl, t_ray r);
t_hit_point                 inter_colin(t_cylinder *cyl, t_ray r);
t_hit_point                 hit_cylinder(void *o, t_ray r);


/*plan.c*/

t_plan                       *new_plan(t_vect origin, t_vect normal);
t_hit_point			        hit_ortho(t_ray r, t_plan *p, t_vect min);
t_hit_point                   hit_plan(void *o, t_ray r);

/*sphere.c*/

t_sphere                         *new_sphere(t_vect v1, float rad);
t_vect                         normal_sphere(t_sphere *sp, t_vect p);
t_hit_point                    hit_sphere(void *o, t_ray r);


/*virtual_screen*/

t_vect              vectv(t_vect n);
t_vect              vectw(t_vect n);


t_hit_point         (*get_obj_collider(int id))(void *o, t_ray r);








void		        build_obj(t_obj *obj, int obj_type, t_mater *mater, void *type);


void 	        	sum_sphere(t_sphere *sp, float *x, float *y, float *z);
void 	        	sum_plan(t_plan *p, float *x, float *y, float *z);
void 	             sum_cylinder(t_cylinder *cyl, float *x, float *y, float *z);
void 	    	    sum_cone(t_cone* c, float *x, float *y, float *z);
void	            add_coord1(t_obj *obj, float *x, float *y, float *z);
void	            add_coord2(t_obj *obj, float *x, float *y, float *z);

#endif
