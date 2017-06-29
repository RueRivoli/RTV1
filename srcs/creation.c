/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:51:15 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/09 11:51:22 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cam           *new_cam(t_vect v1, t_vect v2, float phi, float theta)
{
	t_cam *c;
	if (!(c = (t_cam *)malloc(sizeof(t_cam*))))
	c->pos = v1;
	c->trans = v2;
	c->add_phi = phi;
	c->add_theta = theta;
	return (c);
}

t_mater         *new_mater(float f, int r, int g, int b)
{
	t_mater *mat;
	if (!(mat = (t_mat *)malloc(sizeof(t_mat*)))
	mat->alpha = f;
	mat->ir = r;
	mat->ig = g;
	mat->ib = b;
	return (mat);
}

t_hit_point     new_hit_point(t_vect vect, float dist_to_cam, t_vect normal, int form)
{
	t_hit_point ht;
	ht.vect = vect;
	ht.distance_to_cam = dist_to_cam;
	ht.normal = normal;
	ht.form = form;
	return (ht);
}

t_hit_point		hp_null(void)
{
	t_vect v;

	v = new_vect(0,0,0);
	hp = new_hit_point(v, 0.0, v, 0);
	return (hp);
}

t_ray           new_ray(t_vect orig, t_vect dir, float fl, t_vect color)
{
	t_ray r;
	r.origin = orig;
	r.direction = dir;
	r.dist_to_screen = fl;
	r.color = color;
	return (r);
}

t_obj       *add_obj(t_obj *obj, int obj_type, t_mater *mater, void *type)
{
	t_obj *tmp;
	t_obj  *new;
	if (!obj)
	{
		if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
			return (NULL);
		build_obj(obj, obj_type, mater, type);
	}
	else 
	{
		tmp = obj;
		while (tmp->next)
			tmp = tmp->next;
		new = (t_obj*)malloc(sizeof(t_obj));
		build_obj(new, obj_type, mater, type);
		tmp->next = new;
	}
	return (obj);
}
