/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:51:04 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 16:05:16 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light		*add_light(t_light *light, t_vect pos)
{
	t_light		*tmp;
	t_light		*new;

	if (!light)
	{
		if (!(light = (t_light*)malloc(sizeof(t_light))))
			return (NULL);
		build_light(light, pos);
	}
	else
	{
		tmp = light;
		while (tmp->next)
			tmp = tmp->next;
		new = (t_light*)malloc(sizeof(t_light));
		build_light(new, pos);
		tmp->next = new;
	}
	return (light);
}

float		coef_lambert(t_light *light, t_hit_point hp)
{
	t_vect		v;
	t_vect		min;
	float		res;

	v = vect_null();
	min = vect_null();
	res = 0.0;
	min = min_vect(light->pos, hp.vect);
	normed(&min);
	v = multiply_scalar(min, 1.0);
	normed(&hp.normal);
	res = scalar_product(hp.normal, v);
	if (hp.form == 2)
		res = max(max(-res, res), 0.0);
	else
		res = max(res, 0.0);
	return (res);
}

void		find_color_light(t_light *light, t_hit_point hp, \
		t_mater *mat, t_vect *v)
{
	float	lambert;

	lambert = 0.0;
	lambert = coef_lambert(light, hp);
	if (lambert >= 0.0)
	{
		v->x += lambert * mat->ir * light->red;
		v->y += lambert * mat->ig * light->green;
		v->z += lambert * mat->ib * light->blue;
	}
}

void		find_color_sha(t_light *light, t_hit_point hp, \
		t_mater *mat, t_vect *v)
{
	float	lambert;

	lambert = 0.0;
	lambert = coef_lambert(light, hp);
	v->x += lambert * mat->ir * (light->red / 2);
	v->y += lambert * mat->ig * (light->green / 2);
	v->z += lambert * mat->ib * (light->blue / 2);
}

int			numberoflights(t_env *env)
{
	int		ct;
	t_light	*light;

	ct = 0;
	light = env->light;
	while (light)
	{
		light = light->next;
		ct++;
	}
	return (ct);
}
