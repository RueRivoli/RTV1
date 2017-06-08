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


#define INFINI 100000000.0
#define PI 3.14159

typedef struct s_cam
{
    t_vect      *pos;
    t_vect      *trans;
    float       add_phi;
    float       add_theta;
}               t_cam;

typedef struct s_screen 
{
    t_vect      *center;
    t_vect      *v;
    t_vect      *w;
    int         nx;
    int         ny;

}               t_screen;

typedef struct s_light 
{
    t_vect          *pos;
    //t_vect          *direction;
    float           red;
    float           green;
     float           blue;
     struct s_light *next;
}               t_light;


typedef struct s_win
{
    SDL_Window  *handle;
    SDL_Renderer *rend;
    int         width;
    int         height;
}               t_win;


typedef struct s_env
{
    t_win           *win;
    t_screen        *screen;
    t_cam           *cam;
    t_light         *light;
    t_ray            *ray;
    t_obj            *obj;
    int             boucle;
    SDL_Surface     *background;
    char            *title;
    int             size_x;
    int             size_y;
    int             x;
    int             y;
    int             z;
}               t_env;

t_light       *add_light(t_light *light, t_vect *pos);
float           coef_lambert(t_light *light, t_hit_point *h);
t_vect          *find_color(t_light *light, t_hit_point *hp, t_mater *mat);
t_env           *init_env(void);
void            render(t_env *env);
int             event(t_env *env);
t_cam           *new_cam(t_vect *v1, t_vect *trans, float phi, float theta);
t_ray           *new_ray(t_vect *orig, t_vect *dir, float fl, t_vect *color);
void            quit_SDL(t_env *env);
void            trace(t_env *env);
void             trace2(t_env *env);
float           term(float alpha, float beta);
void             error_param();
t_hit_point     *new_hit_point(t_vect *vect, float dist_to_cam, t_vect *normal, int form);

int             type_objects(char *str);

int             register_sphere(char *line, t_env *env, int fd);
int             registering(int to, char *line, t_env *env, int fd);
int              read_scene(int fd, char *line, t_env *env);
int              lecture(int fd, t_env *env);
void            display_scene(t_env *env);
int             read_objects(int fd, char *line, t_env *env);
t_vect          *center_average(t_env *env);
float           distance_with_cam(t_env *env, t_hit_point *hp);
void            set_virtual_screen(t_env *env);
void            raytrace(t_env *env);
float           norm(t_vect *v);
int             colin(t_vect *v, t_vect *w);
float           calcul(t_env *env, t_hit_point *hp);

t_vect          *origin(int to, void *o);
t_vect           *normal(int to, void *o);
void              modify(void *o, char *line, int fd, int to);
int               numberoflights(t_env *env);

t_vect            *find_color_light(t_light *light, t_hit_point *hp, t_mater *mat, t_vect *v);
t_vect            *find_color_sha(t_light *light, t_hit_point *hp, t_mater *mat, t_vect *v);
void                SDL_render(t_env *env);
void                refresh(t_env *env);
void                find_angle(t_env *env, t_ray *ray);
int                 find_nearest_inter(t_env *env, t_vect *v, t_hit_point **mem, t_obj **colore);
int                     is_light_reached(t_light *light, t_env *env, t_hit_point *mem, t_obj *colore);
t_vect                *put_on_light(t_env *env,t_hit_point *mem, t_obj *colore);
void            choose_color(t_env *env, t_hit_point *mem, t_obj *colore);
#endif
