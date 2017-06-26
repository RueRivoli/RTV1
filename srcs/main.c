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

int            find_nearest_inter(t_env *env, t_vect *v, t_hit_point **mem, t_obj **colore)
{
	t_ray *r;
	t_obj *tmp;
	t_hit_point *hp;
	float min;
	int p;

	tmp = env->obj;
	min = INFINI;
	hp = NULL;
	p = 0;
	r = current_ray(env, v);
	while (tmp)
	{   
		if ((hp = tmp->is_hit(tmp->type, r)))
		{
			hp->distance_to_cam = distance_with_cam(env, hp);
			if (hp->distance_to_cam < min)
			{
				min = hp->distance_to_cam;
				*colore = tmp;
				if (p > 0)
					free_hit_point(*mem);
				*mem = hp;
				p++;
			}
			else
            	free(hp);
		}
		tmp = tmp->next;
	}
	
	free_ray(r);
	free(tmp);
	
	return (min);
}

int        is_light_reached(t_light *light, t_env *env, t_hit_point *mem, t_obj *colore)
{
	t_vect *mini;
	t_vect *w;
	t_ray *r;
	t_obj *tmp;
	t_hit_point *hr;
	t_vect *intersect;
	int meet_object;

	hr = NULL;
	meet_object = 0;
	intersect = new_vect(mem->vect->x, mem->vect->y, mem->vect->z);
	mini = minus_vect(light->pos, intersect);
	normed(mini);
	w = new_vect(0.0, 0.0, 0.0);
	r = new_ray(intersect, mini, 0.0, w);
	tmp = env->obj;
	while (tmp && !meet_object)
	{   
		if (tmp == colore)
			tmp = tmp->next;
		else if (!(hr = tmp->is_hit(tmp->type, r)))
			tmp = tmp->next;
		else
		{
			if (distance(mem->vect, hr->vect) < distance(hr->vect, light->pos))
			{
				free_hit_point(hr);
				return (1);
			}
				free_hit_point(hr);
				tmp = tmp->next;	
		}
	}
	free_ray(r);
	free(tmp);
	return (0);
}

void               put_on_light(t_env *env, t_hit_point *mem, t_obj *colore, int p, int q)
{
    t_light *light;
	t_vect *col;
	float nb_of_lights;
	int meet_object;

	light = env->light;
	nb_of_lights = numberoflights(env);
	col = new_vect(0, 0, 0);
	while (light)
	{   
		meet_object = is_light_reached(light, env, mem, colore);
		if (!meet_object)
			find_color_light(light, mem, colore->mater, col);
		else
			find_color_sha(light, mem, colore->mater, col);
		light = light->next;
	}
	SDL_SetRenderDrawColor(env->win->rend, (int)(col->x / (255 * nb_of_lights)), (int)(col->y / (255 * nb_of_lights)), (int)(col->z / (255 * nb_of_lights)), 255);
	SDL_RenderDrawPoint(env->win->rend, p, q);
	free(col);
}

void        raytrace_thread(t_env *env, int pi, int pf)
{
	t_vect *v;
	t_obj *colore;
	t_hit_point *mem;
    int p;
	int q;
	float min;

	colore = NULL;
	mem = NULL;
	p = pi;
     
	while (p < pf)
	{
		q = 0;
		while (q < env->size_y)
		{   
			min = INFINI;
			v = new_vect(p + env->cam->trans->x, q + env->cam->trans->y, env->cam->trans->z);
			min = find_nearest_inter(env, v, &mem, &colore);
            free(v);
			if (min < INFINI && mem)
			{   
				put_on_light(env, mem, colore, p, q);
				free_hit_point(mem);
			}
			q++;
		}
		p++;    
	}
}


/*void        raytrace(t_env *env)
{
	t_vect *v;
	t_obj *colore;
	t_hit_point *mem;
    int p;
	int q;
	float min;

	colore = NULL;
	mem = NULL;
	p = 0;
     
	while (p < env->size_x)
	{
		q = 0;
		while (q < env->size_y)
		{   
			min = INFINI;
			v = new_vect(p + env->cam->trans->x, q + env->cam->trans->y, env->cam->trans->z);
			min = find_nearest_inter(env, v, &mem, &colore);
            free(v);
			if (min < INFINI && mem)
			{   
				put_on_light(env, mem, colore, p, q);
				free_hit_point(mem);
			}
			q++;
		}
		p++;    
	}
}
*/

int              main(int argc, char **argv)
{
	t_env *env;
	t_win *win;
	t_arg *arg;
	t_light *l;
	t_light *tmp;
	t_obj *o;
	t_obj *tp;
    int fd;

	if (!(arg = (t_arg*)malloc(sizeof(t_arg) * NB_THREAD + 1)))
		return (0);
	/*if (!(arg->env = (t_env*)malloc(sizeof(t_env) * NB_THREAD + 1)))
		return (0);*/
	if (!(env = init_env(arg)))
		return (0);
	win = env->win;
	if (argc != 2)
	{
		error_param();
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	/*Lecture et affichage de la scene*/
	if (fd > 0 && lecture(fd, env) != 0)
		display_scene(env);
	else
	{
		error_param();
		return (0);
	}
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
		return (0);
	
	/*Placement de l'ecran virtuel*/

	//set_virtual_screen(env);

	win->handle = SDL_CreateWindow("RTV1", 650, 300, env->size_x, env->size_y, 0);
	win->rend = SDL_CreateRenderer(env->win->handle, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_SOFTWARE);
	//SDL_CreateWindowAndRenderer(win->width, win->height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &win->handle, &win->rend);
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

	free(arg);
	free(env->cam);
	free(env->win);
	 free(env->obj);
    //free(env->screen->center);
    free(env->title);
    free(env->background);
	free(env);
	l = env->light;
	while (l)
	{ 
		if (l->next)
			tmp = l->next;
		free(l);
		l = tmp;
	}	
	o = env->obj;
	while (o)
	{ 
		if (o->next)
			tp = o->next;
		free(o);
		o = tp;
	}
   
	return (0); 
}
