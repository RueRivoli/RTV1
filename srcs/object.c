/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essai.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:55:31 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 18:24:33 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_hit_point			(*get_obj_collider(int id))(void *o, t_ray r)
{
	if (id == 1)
		return (*hit_sphere);
	if (id == 2)
		return (*hit_plan);
	if (id == 3)
		return (*hit_cylinder);
	if (id == 4)
		return (*hit_cone);
	return (NULL);
}

float				distance_with_cam(t_env *env, t_hit_point hp)
{
	t_vect		diff;
	float		dis;

	if (equals_hp(hp, hp_null()) == 1)
		return (INFINI);
	if (hp.distance_to_cam == -1.0)
		return (0.0);
	diff = min_vect(env->cam->pos, hp.vect);
	dis = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
	return (dis);
}
