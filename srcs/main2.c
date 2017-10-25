/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:54:51 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 18:21:51 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"
#include "../include/event.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int					parsing(t_env *env, int argc, char **argv)
{
	t_win	*win;
	int		fd;

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
	env->nb_of_lights = numberoflights(env);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
		return (0);
	win->handle = SDL_CreateWindow("RTV1", 300, 200, env->screen->nx, \
			env->screen->ny, 0);
	win->rend = SDL_CreateRenderer(env->win->handle, 1, \
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_SOFTWARE);
	return (1);
}

t_hit_point			compare_distance(t_hit_point mem, t_hit_point hp, \
		float *minimum, t_hit_point nearest_hp)
{
	if (distance(mem.vect, hp.vect) < *minimum)
	{
		nearest_hp = hp;
		*minimum = distance(mem.vect, hp.vect);
	}
	return (nearest_hp);
}

void				throw_ray(t_env *env, t_obj *obj_met, float p, float q)
{
	t_ray			r;
	t_hit_point		nearest_hp;
	float			pr;
	float			qr;
	float			min;

	min = INFINI;
	nearest_hp = hp_null();
	pr = ((p + 0.5) / env->screen->nx) + env->cam->pos.x - 0.5 + \
		env->cam->trans.x;
	qr = ((q + 0.5) / env->screen->ny) + env->cam->pos.y - 0.5 + \
		env->cam->trans.y;
	min = distance_with_next_intersection(env, new_vect(pr, qr, \
				env->cam->pos.z
				+ env->cam->trans.z + 1), &obj_met);
	r = current_ray(env, new_vect(pr, qr, env->cam->pos.z + \
				env->cam->trans.z + 1));
	nearest_hp = nearest_point(env, r, &obj_met);
	if (min < INFINI && equals_hp(nearest_hp, hp_null()) == 0)
	{
		put_on_light(env, nearest_hp, obj_met);
		SDL_RenderDrawPoint(env->win->rend, p, q);
	}
}

void				close_main(t_env *env, t_arg *arg)
{
	SDL_RenderPresent(env->win->rend);
	while (!env->boucle)
	{
		if (event(env, arg) == 0)
			env->boucle = 1;
	}
	SDL_DestroyWindow(env->win->handle);
	SDL_DestroyRenderer(env->win->rend);
	quit_sdl(env);
}
