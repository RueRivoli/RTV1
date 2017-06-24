/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:51:04 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/09 11:51:08 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


t_light       *add_light(t_light *light, t_vect *pos)
{
	t_light *tmp;
	t_light *new;
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

float       coef_lambert(t_light *light, t_hit_point *hp)
{
	t_vect *v;
	t_vect *min;
	float res;

	min = minus_vect(light->pos, hp->vect);
	normed(min);
	v = multiply_scalar(min, 1.0);
	normed(hp->normal);
	res = scalar_product(hp->normal, v);
	free(v);
	free(min);
	if (hp->form == 2)
		res = max(max(-res, res), 0.0);
	else
		res = max(res, 0.0);
	return (res);
}

t_vect      *find_color_light(t_light *light, t_hit_point *hp, t_mater *mat, t_vect *v)
{
	t_vect *new_color;
	float lambert;

	lambert = coef_lambert(light, hp);
	new_color = new_vect((lambert * mat->ir * light->red) + v->x , (lambert * mat->ig * light->green) + v->y, (lambert * mat->ib * light->blue) + v->z);
	//new_color = new_vect((lambert * mat->ir * light->red + 0.1 * mat->ir * light->red) / (1.1 * 255) , (lambert * mat->ig * light->green + 0.1 * mat->ig * light->green) / (1.1 * 255), (lambert * mat->ib * light->blue + 0.1 * mat->ib * light->blue) / (1.1 * 255));
	free(v);
	return (new_color);
}

t_vect      *find_color_sha(t_light *light, t_hit_point *hp, t_mater *mat, t_vect *v)
{
	t_vect *new_color;
	float lambert;

	lambert = coef_lambert(light, hp);
	new_color = new_vect(((lambert * mat->ir * light->red) / 2.0) + v->x , (lambert * mat->ig * light->green / 2.0) + v->y, (lambert * mat->ib * light->blue / 2.0)+ v->z);
	//new_color = new_vect((lambert * mat->ir * light->red + 0.1 * mat->ir * light->red) / (1.1 * 255) , (lambert * mat->ig * light->green + 0.1 * mat->ig * light->green) / (1.1 * 255), (lambert * mat->ib * light->blue + 0.1 * mat->ib * light->blue) / (1.1 * 255));
	free(v);
	return (new_color);
}

int         numberoflights(t_env *env)
{
	int ct;
	t_light *light;
	ct = 0;
	light = env->light;
	while (light)
	{
		light = light->next;
		ct++;
	}
	return (ct);
}
