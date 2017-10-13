/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:23:34 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 17:49:17 by fgallois         ###   ########.fr       */
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
#include <SDL_thread.h>

#define INFINI 100000000.0
#define PI 3.14159
#define NB_THREAD 8

typedef struct s_cam
{
	t_vect      pos;
	t_vect      trans;
	float       add_phi;
	float       add_theta;
}               t_cam;

typedef struct s_screen 
{
	t_vect      center;
	t_vect      v;
	t_vect      w;
	int         nx;
	int         ny;

}               t_screen;

typedef struct s_light 
{
	t_vect          pos;
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
	t_obj            *obj;
	int             boucle;
	SDL_Surface     *background;
	pthread_t       **thread;
	int             thread_cnt;
	char            *title;
	int             size_x;
	int             size_y;
	int             nb_of_lights;
	int             x;
	int             y;
	int             z;
}               t_env;


typedef struct s_arg {
	t_env *env;
	int     i;
}               t_arg;

typedef struct data {
	t_env *env ;
	pthread_mutex_t mutex;
} data;


/*creation.c*/

t_hit_point 		hp_null(void);

/*display1.c*/


void                display_camera(t_env *env);
void                 display_light(t_env *env);
void                display_sphere(t_sphere *sp, t_mater *mat);
void                display_mat(t_mater *mat);
void                display_plan(t_plan *p, t_mater *mat);

/*display2.c*/

void                display_cylinder(t_cylinder *cyl, t_mater *mat);
void                display_cone(t_cone *cone, t_mater *mat);

/*error.c*/

void                    error_param();
void                    build_light(t_light *light, t_vect pos);
float                  term(float alpha, float beta);
int                    event(t_env *env, t_arg *arg);


/*event.c*/

void                     refresh(t_env *env, t_arg *arg);
int                     key_event_bis(t_env *env, SDL_Event event);
void                    key_event(t_env *env, SDL_Event event, t_arg *arg);
void                    quit_sdl(t_env *env);

/*free.c*/

void                     free_tab(char **tab);

/*init_env.c*/

t_env                *init_env(t_arg *arg);

/*light1.c*/

t_light             *add_light(t_light *light, t_vect pos);
float                coef_lambert(t_light *light, t_hit_point hp);

void                find_color_light(t_light *light, t_hit_point hp, t_mater *mat, t_vect *v);
void               find_color_sha(t_light *light, t_hit_point hp, t_mater *mat, t_vect *v);
int                   numberoflights(t_env *env);

/*main.c*/
void		        rotate_vector(t_env *env, t_vect *ray_dir);
t_ray		        current_ray(t_env *env, t_vect v);
void                  raytrace(t_env *env);

t_hit_point		    nearest_point(t_env *env, t_ray ray, t_obj **obj_met);
t_hit_point			nearest_point_after_object(t_env *env, t_ray ray, t_hit_point mem, t_obj *obj_met);

float               distance_with_next_intersection(t_env *env, t_vect v, t_obj **colore);
int                     is_light_reached(t_light *light, t_env *env, t_hit_point mem, t_obj *colore);
void                   put_on_light(t_env *env, t_hit_point mem, t_obj *colore);
void                	raytrace_thread(t_env *env, int pi, int pf);
t_hit_point			compare_distance(t_hit_point mem, t_hit_point hp, float *minimum, t_hit_point nearest_hp);
void				throw_ray(t_env *env, t_obj *obj_met, float p, float q);
int					parsing(t_env *env, int argc, char **argv);
void				close_main(t_env *env, t_arg *arg);
/*modify.c*/

void                  translation(char *line, void *o, int to);
void                rotation(char *line, void *o, int to);
void                rotation_y(char *line, void *o, int to);
void                rotation_z(char *line, void *o, int to);
void               modify(void *o, char *line, int fd, int to);

/*object.c*/

float               distance_with_cam(t_env *env, t_hit_point hp);

/*parser.c*/
t_vect 				origin0(int to, void *o);
t_vect      		origin(int to, void *o);
t_vect     	    	 normal(int to, void *o);
int 	        	start_reading(int fd, char *line, t_env *env, int *index);
int                  lecture(int fd, t_env *env);
void				class(int to, void *o, float f, int n);
void				apply_rotate(int to, void *o, float f, int n);

/*read_object.c*/


int                  type_objects(char *str);
int                    read_scene(int fd, char *line, t_env *env);

/*read.c*/

int                    read_name(int fd, char *line, t_env *env);
int                     read_camera(int fd, char *line, t_env *env);
int                    read_render(int fd, char *line, t_env *env);
int                    read_spot(int fd, char *line, t_env *env);


/*register_object.c*/

int                     register_sphere(char *line, t_env *env, int fd);



/*thread.c*/


pthread_t			**malloc_thread(int count, t_arg *arg, void *a);
void				redraw(t_env *env, t_arg *arg);

/*thread1.c*/

int                 thread_function(void* addr);
void			    fill_arg(t_arg *arg, void *a);
void                boucle(t_arg *arg, t_env *env);


/*virtual_screen.c*/


/**/

/*creation.c*/
t_cam                   *new_cam(t_vect v1, t_vect v2, float phi, float theta);
t_hit_point             new_hit_point(t_vect vect, float dist_to_cam, t_vect normal, int form);
t_ray                   new_ray(t_vect orig, t_vect dir, float fl, t_vect color);



t_vect               find_color(t_light *light, t_hit_point *hp, t_mater *mat);

void                  render(t_env *env);









int                    registering(int to, char *line, t_env *env, int fd);

int                    lecture(int fd, t_env *env);
void                  display_scene(t_env *env);
int                 read_objects(int fd, char *line, t_env *env);
t_vect               center_average(t_env *env);

void                 set_virtual_screen(t_env *env);


float                 calcul(t_env *env, t_hit_point *hp);

t_vect                  origin(int to, void *o);
t_vect                   normal(int to, void *o);




void                SDL_render(t_env *env);

void                  find_angle(t_env *env, t_ray ray);

void                  choose_color(t_env *env, t_hit_point *mem, t_obj *colore);

t_vect                 vect_central(t_env *env);
t_vect                    vect_basic(void);
float                  phi(t_vect v);
float                  theta(t_vect v);
float                  add_phi(t_env *env);
float                       add_theta(t_env *env);
void                    change_vect(t_vect *v, float phi, float theta);



t_vect                  read_origin(char *line, int fd, char *str);
float                   read_float(char *line, int fd, char *str);
t_mater                 *read_mater(char *line, int fd, char *str);
t_vect                  origin0(int to, void *o);
int		            start_reading(int fd, char *line, t_env *env, int *index);

void                  accord_to_form(t_obj *obj, t_mater *mat);


int		                 equals_hp(t_hit_point h1, t_hit_point h2);  

t_vect 		            vect_col(t_env *env);




#endif
