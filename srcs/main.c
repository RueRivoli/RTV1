/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:54:51 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/09 11:49:49 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/rtv1.h"
#   include "../include/event.h"
# include <SDL2/SDL.h>
# include <stdlib.h>
#include <stdio.h>
# include <math.h>


void		rotate_vector(t_env *env, t_vect *ray_dir)
{
	float plus_phi;
	float plus_theta;

	plus_phi = env->cam->add_phi;
	plus_theta = env->cam->add_theta;
	change_vect(ray_dir, plus_phi, plus_theta);
}

t_ray		*current_ray(t_env *env, t_vect *v)
{
	t_ray *r;
	t_vect *mini;
	t_vect *w;
	t_vect *ray_dir;
	t_vect  *new_pos_cam;

	new_pos_cam = add_vect(env->cam->pos, env->cam->trans);
	mini = minus_vect(v, new_pos_cam);
	w = new_vect(0.0, 0.0, 0.0);
	ray_dir = mini;

	rotate_vector(env, ray_dir);
    normed(ray_dir);
	r = new_ray(new_pos_cam, ray_dir, norm(mini), w);
	return (r);
}

t_hit_point		*closest_point(t_env *env, t_ray *ray, t_obj **obj_rencontre)
{
	t_obj *tmp;
	t_hit_point *hp;
	t_hit_point	*closest_hpoint;
	int minimal_distance;
	int ct;

	tmp = env->obj;
	minimal_distance = INFINI;
	ct = 0;
	closest_hpoint = NULL;
	while (tmp)
	{
		if ((hp = tmp->is_hit(tmp->type, ray)))
		{
			hp->distance_to_cam = distance_with_cam(env, hp);
			if (hp->distance_to_cam < minimal_distance)
			{
				if (ct > 0)
					free(closest_hpoint);
				closest_hpoint = hp;
				minimal_distance = hp->distance_to_cam;
				*obj_rencontre = tmp;
				ct++;
			}
			else
				free(hp);
		}
		tmp = tmp->next;
	}
	free(tmp);
	return (closest_hpoint);
}

float            distance_to_next_intersection(t_env *env, t_vect *v, t_obj **obj_rencontre)
{
	t_ray *r;
	t_hit_point *closest_hpoint;
	float distance;
	r = current_ray(env, v);
	closest_hpoint = closest_point(env, r, obj_rencontre);
	free_ray(r);
	if (closest_hpoint)
	{
		distance = closest_hpoint->distance_to_cam;
		free(closest_hpoint);
		return (distance);
	}
	else
			return (INFINI);
}


int        is_light_reached(t_light *light, t_env *env, t_hit_point *mem, t_obj *obj_obstruction)
{
	t_vect *mini;
	t_vect *w;
	t_ray *r;
	t_hit_point *closest_hpoint;
	t_vect *intersect;
	int res;

	intersect = new_vect(mem->vect->x, mem->vect->y, mem->vect->z);
	mini = minus_vect(light->pos, intersect);
	normed(mini);
	w = new_vect(0.0, 0.0, 0.0);
	r = new_ray(intersect, mini, 0.0, w);
	closest_hpoint = closest_point(env, r, &obj_obstruction);
	if (closest_hpoint)
	{
		res = distance(closest_hpoint->vect, light->pos) - distance(mem->vect, closest_hpoint->vect);
		free_hit_point(closest_hpoint);
		free_ray(r);
	if (res > 0)
		return (0);
	}
		return (1);
}

void               put_on_light(t_env *env, t_hit_point *mem, t_obj *obj_rencontre, int p, int q)
{
    t_light *light;
	t_obj *obj_obstruction;
	t_vect *col;
	float nb_of_lights;

	light = env->light;
	obj_obstruction = NULL;
	nb_of_lights = numberoflights(env);
	col = new_vect(0, 0, 0);
	while (light)
	{   
		if (is_light_reached(light, env, mem, obj_obstruction))
			find_color_light(light, mem, obj_rencontre->mater, col);
		else
			find_color_sha(light, mem, obj_rencontre->mater, col);
		light = light->next;
	}
	SDL_SetRenderDrawColor(env->win->rend, (int)(col->x / (255 * nb_of_lights)), (int)(col->y / (255 * nb_of_lights)), (int)(col->z / (255 * nb_of_lights)), 255);
	SDL_RenderDrawPoint(env->win->rend, p, q);
	free(col);
}

void        raytrace_thread(t_env *env, int pi, int pf)
{
	t_vect *v;
	t_obj *obj_rencontre;
	t_obj *obj_obstruction;
	t_hit_point *closest_hpoint;
	t_ray *r;
    int p;
	int q;
	float min;

	obj_rencontre = NULL;
	obj_obstruction = NULL;
	p = pi;
     
	while (p < pf)
	{
		q = 0;
		while (q < env->size_y)
		{   
			min = INFINI;
			v = new_vect(p + env->cam->trans->x, q + env->cam->trans->y, env->cam->trans->z);
			min = distance_to_next_intersection(env, v, &obj_rencontre);
			r = current_ray(env, v);
			
			closest_hpoint = closest_point(env, r, &obj_rencontre);
			if (min < INFINI && closest_hpoint)
			{   
				put_on_light(env, closest_hpoint, obj_rencontre, p, q);
				free_hit_point(closest_hpoint);
			}
			free(v);
			free_ray(r);
			q++;
		}
		p++;    
	}
}


int              main(int argc, char **argv)
{
	t_env *env;
	t_win *win;
	t_arg *arg;
    int fd;

	if (!(arg = (t_arg*)malloc(sizeof(t_arg) * NB_THREAD + 1)))
		return (0);
	if (!(env = init_env(arg)))
		return (0);
	win = env->win;
	if (argc != 2)
	{
		error_param();
		return (0);
	}
	fd = open(argv[1], O_RDONLY);

	if (fd > 0 && lecture(fd, env) != 0)
		display_scene(env);
	else
	{
		error_param();
		return (0);
	}
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
		return (0);
	
	win->handle = SDL_CreateWindow("RTV1", 650, 300, env->size_x, env->size_y, 0);
	win->rend = SDL_CreateRenderer(env->win->handle, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
	SDL_RenderClear(env->win->rend);

	//raytrace(env);
	boucle(arg, env);
	//redraw(env, arg);
	SDL_RenderPresent(env->win->rend);
	while(!env->boucle)
	{
		if (event(env, arg) == 0)
			env->boucle = 1;
	}

	SDL_DestroyWindow(env->win->handle);
	SDL_DestroyRenderer(env->win->rend);
	quit_SDL(env);

	return (0); 
}

