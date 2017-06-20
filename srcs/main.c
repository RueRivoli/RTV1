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

int            find_nearest_inter(t_env *env, t_vect *v, t_hit_point **mem, t_obj **colore)
{
	t_vect *mini;
	t_vect *w;
	t_vect *ray_dir;
	t_obj *tmp;
	t_hit_point *hp;
	t_ray *r;
	t_vect  *new_pos_cam;
	float plus_phi;
	float plus_theta;
	//t_vect *new_dir_ray;
	//t_vect *final;
	float min;
	tmp = env->obj;
	min = INFINI;
	//ft_putstr("CHAT");
	new_pos_cam = add_vect(env->cam->pos, env->cam->trans);
	mini = minus_vect(v, new_pos_cam);
	w = new_vect(0.0, 0.0, 0.0);
	ray_dir = mini;
	plus_phi = env->cam->add_phi;
	plus_theta = env->cam->add_theta;
	//if (env->cam->pos->x == 600.0 && env->cam->pos->y == 450.0 && env->cam->pos->z == -100.0)
	// {
	/*if (plus_phi != 0 || plus_theta != 0)
		change_vect(ray_dir, plus_phi, plus_theta);*/
	change_vect(ray_dir, plus_phi, plus_theta);
    normed(ray_dir);
	r = new_ray(new_pos_cam, ray_dir, norm(mini), w);
	//}
	/*else
	  {
	  new_dir_ray = change_vect(ray_dir, plus_phi, plus_theta);
	  printf("NR->X  %f ", new_dir_ray->x);
	  printf("NR->X  %f ", new_dir_ray->y);
	  printf("NR->X %f  \n", new_dir_ray->z);
	  final = normed_vect(new_dir_ray);
	  r = new_ray(env->cam->pos, final, norm(mini), w);
	  }*/
	while (tmp)
	{   
		if ((hp = tmp->is_hit(tmp->type, r)))
		{
			hp->distance_to_cam = distance_with_cam(env, hp);
			if (hp->distance_to_cam < min)
			{
				min = hp->distance_to_cam;
				*colore = tmp;
				*mem = hp;
			}
			else
            	free(hp);
		}
		tmp = tmp->next;
	}
	free(mini);
	free(w);
	free(r);
	return (min);
}

int        is_light_reached(t_light *light, t_env *env, t_hit_point *mem, t_obj *colore)
{
	t_vect *mini;
	t_vect *w;
	t_ray *r;
	t_obj *tmp;
	t_hit_point *hr;
	int meet_object;

	meet_object = 0;
	mini = minus_vect(light->pos, mem->vect);
	normed(mini);
	w = new_vect(0.0, 0.0, 0.0);
	r = new_ray(mem->vect, mini, 0.0, w);
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
				return (1);
			tmp = tmp->next;
			free(hr->vect);
			free(hr->normal);
			free(hr);
		}
	}
    free(w);
	free(r);
	free(mini);
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
	col = new_vect(0.0, 0.0, 0.0);
	while (light)
	{   
		meet_object = is_light_reached(light, env, mem, colore);
		if (!meet_object)
			col = find_color_light(light, mem, colore->mater, col);
		else
			col = find_color_sha(light, mem, colore->mater, col);
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
    //t_vect *pos0;
    int p;
	int q;
    int nb_of_lights;
	float min;

	colore = NULL;
	mem = NULL;
    //pos0 = env->cam->pos;
	//env->cam->pos = add_vect(pos0, env->cam->trans);
    //free(pos0);
	//mem = (t_hit_point*)malloc(sizeof(t_hit_point*));
	nb_of_lights = numberoflights(env);
    //colore = malloc(sizeof(t_obj *));
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
				nb_of_lights = numberoflights(env);
				put_on_light(env, mem, colore, p, q);
				free(mem);
			}
			q++;
		}
		p++;    
	}
   //free(colore);
}


void        raytrace(t_env *env)
{
	t_vect *v;
	t_obj *colore;
	t_hit_point *mem;
    //t_vect *pos0;
    int p;
	int q;
    int nb_of_lights;
	float min;

	colore = NULL;
	mem = NULL;
    //pos0 = env->cam->pos;
	//env->cam->pos = add_vect(pos0, env->cam->trans);
    //free(pos0);
	//mem = (t_hit_point*)malloc(sizeof(t_hit_point*));
	nb_of_lights = numberoflights(env);
    //colore = malloc(sizeof(t_obj *));
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
				nb_of_lights = numberoflights(env);
				put_on_light(env, mem, colore, p, q);
				free(mem);
			}
			q++;
		}
		p++;    
	}
   //free(colore);
}

void            SDL_render(t_env *env)
{
	SDL_Event event;

	SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
	SDL_RenderClear(env->win->rend);
	raytrace(env);
	SDL_RenderPresent(env->win->rend);
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT_RESIZED)
			{
				raytrace(env);
				SDL_RenderClear(env->win->rend);
				return ;
			}
			else if (event.type == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				SDL_RenderClear(env->win->rend);
				return ;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				return ;
			}
			else if (event.type == SDL_QUIT)
				return ;
		}
	}
}


int              main(int argc, char **argv)
{
	t_env *env;
	t_win *win;
	t_arg *arg;
    int fd;

	if (!(arg = (t_arg*)malloc(sizeof(t_arg) *  NB_THREAD + 1)))
		return (0);
	if (!(arg->env = (t_env*)malloc(sizeof(t_env) *  NB_THREAD + 1)))
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

	env->win->handle = SDL_CreateWindow("RTV1", 650, 300, env->size_x, env->size_y, 0);
	env->win->rend = SDL_CreateRenderer(env->win->handle, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_SOFTWARE);
	//SDL_CreateWindowAndRenderer(win->width, win->height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &win->handle, &win->rend);
	SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
	SDL_RenderClear(env->win->rend);
	//SDL_SetWindowTitle(win->handle, "RTV1");


	SDL_RenderClear(env->win->rend);
	//raytrace(env);
	
	redraw(env, arg);
	SDL_RenderPresent(env->win->rend);
	while(!env->boucle)
	{
		if (event(env) == 0)
			env->boucle = 1;
	}
	quit_SDL(env);
	free(env->cam);
	free(env->win);
    free(env->light);
    free(env->obj);
    free(env->screen);
    free(env->title);
    free(env->background);
	free(env);
	return (0); 
}
