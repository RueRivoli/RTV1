/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:23:34 by fgallois          #+#    #+#             */
/*   Updated: 2017/05/12 11:11:22 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "vector.h"
# include "object.h"
# include "../framework/SDL2/include/SDL.h"


# include "../libft/libft.h"

# include <GLUT/GLUT.h>
# include <OpenGL/OpenGL.h>
# include <stdlib.h>
#include <stdio.h>
# include <math.h>      
# include <unistd.h>

typedef struct s_ray 
{   
    t_vect      *origin;
    t_vect      *direction;
}               t_ray;

typedef struct s_cam
{
    t_vect      *pos;
}               t_cam;

typedef struct s_screen 
{
    int         nx;
    int         ny;
}               t_screen;

typedef struct s_light 
{
    t_vect          *pos;
    t_vect          *direction;
    float           red;
    float           green;
     float           blue;
}               t_light;

typedef struct s_light_list
{
        t_light     *current;
        t_light     *next;
}               t_light_list;

typedef struct s_win
{
    SDL_Window  *handle;
    SDL_Renderer *rend;
    int         width;
    int         height;
}               t_win;

typedef struct s_obj
{
    t_vect  *vect;
    int     type;
}           t_obj;

typedef struct s_env
{
    t_win           *win;
    t_screen        *scr;
    t_cam           *cam;
    t_ray            *ray;
    t_obj            *obj;
    int             boucle;
    SDL_Surface     *background;
}               t_env;


t_env       *init_env(void);
void        render(t_env *env);
int        event(t_env *env);
t_cam       *new_cam(t_vect *v1);
t_ray   *new_ray(t_vect *orig, t_vect *dir);
int         belong_to_plan(t_plan *p, t_vect *v);
int         belong_to_sphere(t_sphere *sp, t_vect *v);
void        quit_SDL(t_env *env);
int         hit_sphere(t_sphere *sp, t_ray *r);
int         hit_plan(t_plan *p, t_ray *r);
void        trace(t_env *env);
float       sec_deg_eq(float n, float dir);
float       fst_deg_eq(float n, float dir, float a, float o);
float       zer_deg_eq(float n, float a, float o);

float       sec_deg_eq2(float expr, float n, float dir);
float       fst_deg_eq2(float n, float dir, float a, float o, float expr, float expr2);
float       zer_deg_eq2(float n, float expr2, float o, float a);
int         hit_cylinder2(t_cylinder *cyl, t_ray *r);
int         hit_cylinder3(t_cylinder *cyl, t_ray *r);
#endif
