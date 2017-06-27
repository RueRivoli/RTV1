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

t_ray			*current_ray(t_env *env, t_vect *v)
{
	t_ray 		*r;
	t_vect 		*mini;
	t_vect 		*w;
	t_vect 		*ray_dir;
	t_vect  	*new_pos_cam;

	new_pos_cam = add_vect(env->cam->pos, env->cam->trans);
	mini = minus_vect(v, new_pos_cam);
	w = new_vect(0.0, 0.0, 0.0);
	ray_dir = mini;

	rotate_vector(env, ray_dir);
    normed(ray_dir);
	r = new_ray(new_pos_cam, ray_dir, norm(mini), w);
	return (r);
}

t_hit_point			*nearest_point(t_env *env, t_ray *ray, t_obj **obj_met)
{
	t_obj	*tmp;
	t_hit_point *hp;
	t_hit_point	*nearest_hp;
	float minimum;

	tmp = env->obj;
	minimum = INFINI;
	nearest_hp = NULL;
	
	while (tmp)
	{
		if ((hp = tmp->is_hit(tmp->type, ray)))
		{
			hp->distance_to_cam = distance_with_cam(env, hp);
			if (hp->distance_to_cam < minimum)
			{
					if (nearest_hp)
						free_hit_point(nearest_hp);
					nearest_hp = hp;
					minimum = hp->distance_to_cam;
					*obj_met = tmp;
			}
			else
				free_hit_point(hp);
		}
		tmp = tmp->next;
	}
	free(tmp);
	return (nearest_hp);
}

t_hit_point			*nearest_point_after_object(t_env *env, t_ray *ray, t_hit_point *mem, t_obj *obj_met)
{
	t_obj	*tmp;
	t_hit_point *hp;
	t_hit_point	*nearest_hp;
	float minimum;
	int a;
	tmp = env->obj;
	minimum = INFINI;
	nearest_hp = NULL;
	a = 0;
	
	while (tmp)
	{
		
		if (tmp == obj_met)
			tmp = tmp->next;
		else if ((hp = tmp->is_hit(tmp->type, ray)))
		{
			if (distance(mem->vect, hp->vect) < minimum)
			{
				if (nearest_hp)
					free_hit_point(nearest_hp);
				nearest_hp = hp;
				minimum = distance(mem->vect, hp->vect);
			}
			else
				free_hit_point(hp);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
		
	}
	free(tmp);
	return (nearest_hp);
}

float            distance_with_next_intersection(t_env *env, t_vect *v, t_obj **obj_met)
{
	t_ray *r;
	t_obj *tmp;
	t_hit_point *nearest_hp;
	float distance;
	
	tmp = env->obj;
	distance = INFINI;
	r = current_ray(env, v);
	
	nearest_hp = nearest_point(env, r, obj_met);
	if (nearest_hp)
	{
		distance = nearest_hp->distance_to_cam;
		free_hit_point(nearest_hp);
	}
	free_ray(r);
	return (distance);
}

int        is_light_reached(t_light *light, t_env *env, t_hit_point *mem, t_obj *obj_met)
{
	t_hit_point *nearest_pt;
	t_ray *r;
	t_vect *intersect;
	t_vect *mini;
	t_vect *w;
	float diff;

	
	intersect = new_vect(mem->vect->x, mem->vect->y, mem->vect->z);
	mini = minus_vect(light->pos, intersect);
	normed(mini);
	w = new_vect(0.0, 0.0, 0.0);
	r = new_ray(intersect, mini, 0.0, w);
	nearest_pt = nearest_point_after_object(env, r, mem, obj_met);
	
	free_ray(r);
	if (nearest_pt)
	{
		diff = distance(mem->vect, light->pos) - distance(mem->vect, nearest_pt->vect);
		free_hit_point(nearest_pt);
		if (diff > 0)
			return (0);
	}
	return (1);
}

void               put_on_light(t_env *env, t_hit_point *hp, t_obj *colore, int p, int q)
{
    t_light *light;
	t_vect *col;
	float nb_of_lights;

	light = env->light;
	nb_of_lights = numberoflights(env);
	col = new_vect(0, 0, 0);
	
	while (light)
	{
		if (is_light_reached(light, env, hp, colore))
		{
			find_color_light(light, hp, colore->mater, col);
		}
		else
			find_color_sha(light, hp, colore->mater, col);
		light = light->next;
	}
	SDL_SetRenderDrawColor(env->win->rend, (int)(col->x / (255 * nb_of_lights)), (int)(col->y / (255 * nb_of_lights)), (int)(col->z / (255 * nb_of_lights)), 255);
	SDL_RenderDrawPoint(env->win->rend, p, q);
	free(col);
}

void        raytrace_thread(t_env *env, int pi, int pf)
{
	t_vect *v;
	t_ray *r;
	t_hit_point *nearest_hp;
	t_obj *obj_met;
    int p;
	int q;
	float min;

	obj_met = NULL;
	p = pi;
	while (p < pf)
	{
		q = 0;
		while (q < env->size_y)
		{   
			min = INFINI;
			v = new_vect(p + env->cam->trans->x, q + env->cam->trans->y, env->cam->trans->z);
			min = distance_with_next_intersection(env, v, &obj_met);
			r = current_ray(env, v);
			nearest_hp = nearest_point(env, r, &obj_met);
			
			if (min < INFINI && nearest_hp)
			{   
				put_on_light(env, nearest_hp, obj_met, p, q);
				free_hit_point(nearest_hp);
			}
			free_ray(r);
			free(v);
			q++;
		}
		p++;    
	}
}

void        raytrace(t_env *env)
{
	t_vect *v;
	t_ray *r;
	t_hit_point *nearest_hp;
	t_obj *obj_met;
    int p;
	int q;
	float min;

	obj_met = NULL;
	p = 0;
	
	while (p < 1200)
	{
		q = 0;
		while (q < env->size_y)
		{   
			
			min = INFINI;
			v = new_vect(p + env->cam->trans->x, q + env->cam->trans->y, env->cam->trans->z);
			
			min = distance_with_next_intersection(env, v, &obj_met);
			r = current_ray(env, v);
			nearest_hp = nearest_point(env, r, &obj_met);
			if (min < INFINI && nearest_hp)
			{   
				put_on_light(env, nearest_hp, obj_met, p, q);
				free_hit_point(nearest_hp);
			}
			free_ray(r);
			free(v);
			
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
	/*Lecture et affichage de la scene*/
	
	if (fd > 0 && lecture(fd, env) != 0)
	{
		
		display_scene(env);
		
	}
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

	free(arg);
	free(env->cam);
	free(env->win);
	 free(env->obj);
    free(env->title);
    free(env->background);
	free(env);
	quit_SDL(env);

   sleep(1000000);
	return (0); 
}
