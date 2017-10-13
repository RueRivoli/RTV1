/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 14:35:52 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 18:20:21 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				is_light_reached(t_light *light, t_env *env, t_hit_point mem, \
		t_obj *obj_met)
{
	t_hit_point		nearest_pt;
	t_ray			r;
	t_vect			mini;
	t_vect			w;
	float			diff;

	nearest_pt = hp_null();
	mini = min_vect(light->pos, mem.vect);
	normed(&mini);
	w = vect_null();
	diff = 0.0;
	r = new_ray(mem.vect, mini, 0.0, w);
	nearest_pt = nearest_point_after_object(env, r, mem, obj_met);
	if (nearest_pt.vect.x != 0.0 || nearest_pt.vect.y != 0.0 || \
			nearest_pt.vect.z != 0.0)
		diff = distance(mem.vect, light->pos) - \
			distance(mem.vect, nearest_pt.vect);
	else
		return (1);
	if (diff > 0)
		return (0);
	return (1);
}

void			put_on_light(t_env *env, t_hit_point hp, t_obj *colore)
{
	t_light		*light;
	t_vect		col;

	light = env->light;
	col = vect_col(env);
	while (light)
	{
		if (is_light_reached(light, env, hp, colore))
			find_color_light(light, hp, colore->mater, &col);
		else
			find_color_sha(light, hp, colore->mater, &col);
		light = light->next;
	}
	SDL_SetRenderDrawColor(env->win->rend, (int)(col.x / (255 * \
	(env->nb_of_lights))), (int)(col.y / (255 * (env->nb_of_lights))), \
			(int)(col.z / (255 * (env->nb_of_lights))), 255);
}

float			distance_with_next_intersection(t_env *env, t_vect v, \
		t_obj **obj_met)
{
	t_ray			r;
	t_obj			*tmp;
	t_hit_point		nearest_hp;
	float			distance;

	r = new_ray(vect_null(), vect_null(), 0.0, vect_null());
	tmp = env->obj;
	nearest_hp = hp_null();
	distance = INFINI;
	r = current_ray(env, v);
	nearest_hp = nearest_point(env, r, obj_met);
	if (equals_hp(nearest_hp, hp_null()) == 0)
		distance = nearest_hp.distance_to_cam;
	return (distance);
}
