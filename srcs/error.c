/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essai.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:55:31 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 15:54:52 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		error_param(void)
{
	ft_putstr("Paramètre non conforme\n");
}

void		build_obj(t_obj *obj, int obj_type, t_mater *mater, void *type)
{
	obj->is_hit = g_get_obj_collider(obj_type);
	obj->type = type;
	obj->form = obj_type;
	obj->mater = mater;
	obj->next = NULL;
}

void		build_light(t_light *light, t_vect pos)
{
	light->pos = pos;
	light->red = 255;
	light->green = 255;
	light->blue = 255;
	light->next = NULL;
}

float		term(float alpha, float beta)
{
	return (2 * alpha * beta);
}
