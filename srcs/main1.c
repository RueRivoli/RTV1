/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:54:51 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 17:33:08 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"
#include "../include/event.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

t_ray				current_ray(t_env *env, t_vect v)
{
	t_ray			r;
	t_vect			mini;
	t_vect			w;
	t_vect			ray_dir;
	t_vect			new_pos_cam;

	new_pos_cam = add_vect(env->cam->pos, env->cam->trans);
	mini = min_vect(v, new_pos_cam);
	w = new_vect(0.0, 0.0, 0.0);
	ray_dir = mini;
	rotate_vector(env, &ray_dir);
	normed(&ray_dir);
	r = new_ray(new_pos_cam, ray_dir, norm(&mini), w);
	return (r);
}

t_hit_point			nearest_point(t_env *env, t_ray ray, t_obj **obj_met)
{
	t_obj			*tmp;
	t_hit_point		hp;
	t_hit_point		nearest_hp;
	float			minimum;

	tmp = env->obj;
	minimum = INFINI;
	nearest_hp = hp_null();
	while (tmp)
	{
		hp = tmp->is_hit(tmp->type, ray);
		if (equals_hp(hp, hp_null()) == 0)
		{
			hp.distance_to_cam = distance_with_cam(env, hp);
			if (hp.distance_to_cam < minimum)
			{
				nearest_hp = hp;
				minimum = hp.distance_to_cam;
				*obj_met = tmp;
			}
		}
		tmp = tmp->next;
	}
	free(tmp);
	return (nearest_hp);
}

t_hit_point			nearest_point_after_object(t_env *env, t_ray ray, \
		t_hit_point mem, t_obj *obj_met)
{
	t_obj			*tmp;
	t_hit_point		hp;
	t_hit_point		nearest_hp;
	float			minimum;
	int				a;

	tmp = env->obj;
	minimum = INFINI;
	nearest_hp = hp_null();
	a = 0;
	while (tmp)
	{
		hp = tmp->is_hit(tmp->type, ray);
		if (tmp == obj_met)
			tmp = tmp->next;
		else if (equals_hp(hp, hp_null()) == 0)
		{
			nearest_hp = compare_distance(mem, hp, &minimum, nearest_hp);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	free(tmp);
	return (nearest_hp);
}

void				raytrace_thread(t_env *env, int pi, int pf)
{
	t_ray			r;
	t_hit_point		nearest_hp;
	t_obj			*obj_met;
	float			p;
	float			q;

	obj_met = NULL;
	nearest_hp = hp_null();
	r = new_ray(vect_null(), vect_null(), 0.0, vect_null());
	p = (float)pi;
	while (p < pf)
	{
		q = 0.0;
		while (q < env->screen->ny)
		{
			throw_ray(env, obj_met, p, q);
			q++;
		}
		p++;
	}
}

int					main(int argc, char **argv)
{
	t_env		*env;
	t_arg		*arg;

	if (!(arg = (t_arg*)malloc(sizeof(t_arg) * NB_THREAD + 1)))
		return (0);
	if (!(arg->env = (t_env*)malloc(sizeof(t_env) * NB_THREAD + 1)))
		return (0);
	env = arg->env;
	if (!(env = init_env(env)))
		return (0);
	if (!(env->thread = malloc_thread(NB_THREAD, arg, (void*)env)))
		return (0);
	if (parsing(env, argc, argv) == 0)
		return (0);
	SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
	SDL_RenderClear(env->win->rend);
	boucle(arg, env);
	close_main(env, arg);
	free_env(env);
	
	return (0);
}
