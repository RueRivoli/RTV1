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

t_cam   *new_cam(t_vect *v1, t_vect *v2, float phi, float theta)
{
	t_cam *c;
	if (!(c = (t_cam*)malloc(sizeof(t_cam))))
		return (NULL);
	c->pos = v1;
	c->trans = v2;
	c->add_phi = phi;
	c->add_theta = theta;
	return (c);
}

t_mater   *new_mater(float f, int r, int g, int b)
{
	t_mater *mat;
	if (!(mat = (t_mater*)malloc(sizeof(t_mater))))
		return (NULL);
	mat->alpha = f;
	mat->ir = r;
	mat->ig = g;
	mat->ib = b;
	return (mat);
}

t_vect      *center_average(t_env *env)
{   
	t_obj *obj;
	obj = env->obj;
	float x;
	float y;
	float z;
	int ct;
	ct = 0;
	x = 0;
	y = 0;
	z = 0;
	while (obj)
	{
		ct++;
		if (obj->form == 1)
		{
			t_sphere *sp;
			sp = (t_sphere*)obj->type;
			x += sp->origin->x;
			y += sp->origin->y;
			z += sp->origin->z;
		}
		else if (obj->form == 2)
		{
			t_plan *p;
			p = (t_plan*)obj->type;
			x += p->origin->x;
			y += p->origin->y;
			z += p->origin->z;
		}
		else if (obj->form == 3)
		{
			t_cylinder *cyl;
			cyl = (t_cylinder*)obj->type;
			x += cyl->origin->x;
			y += cyl->origin->y;
			z += cyl->origin->z;
		}
		else if (obj->form == 4)
		{
			t_cone *c;
			c = (t_cone*)obj->type;
			x += c->summit->x;
			y += c->summit->y;
			z += c->summit->z;
		}
		obj = obj->next;
	}
	return (new_vect(x/ct, y/ct, z/ct));
}

t_vect      *vectv(t_vect *n)
{
	float x;
	float y;
	float z;
	t_vect *v;
	x = 1.0;
	y = -n->x /n->y;
	z = 0.0;
	v = new_vect(x, y, z);
	normed(v);
	return (v);
}

t_vect      *vectw(t_vect *n)
{
	float x;
	float y;
	float z;
	t_vect *v;
	t_vect *w;
	y = -0.5 * n->z / (n->y + pow(n->x, 2)/ n->y);
	x = (n->x / n->z) * y;
	z = 0.5;
	v = new_vect(x, y, z);
	w = normed_vect(v);
	free(v);
	return (w);
}


t_vect    *vect_central(t_env *env)
{
	t_vect *dir;
	t_vect *min;

	dir = center_average(env);
	min = minus_vect(dir, env->cam->pos);
	free(dir);
	normed(min);
	return (min);
}

t_vect         *vect_basic()
{
	t_vect *inter;
	t_vect *eye_center;
	t_vect *pix_center;

	eye_center = new_vect(600.0, 450.0, -100.0);
	pix_center = new_vect(600.0, 450.0, 0.0);
	inter = minus_vect(pix_center, eye_center);
	free(eye_center);
	free(pix_center);
	normed(inter);
	return (inter);
}

float      phi(t_vect *v)
{
	return (acos(v->y / norm(v)));
}

float      theta(t_vect *v)
{
	float phi0;
	phi0 = phi(v);
	return (asin(v->x / (norm(v) * sin(phi0))));
}

float       add_phi(t_env *env)
{
	t_vect *central;
	t_vect *basic;
	float phi0;

	basic = vect_basic();
	central = vect_central(env);
	phi0 = phi(central) - phi(basic);
	free(basic);
	free(central);
	return (phi0);
}

float       add_theta(t_env *env)
{
	t_vect *central;
	t_vect *basic;
	float theta0;

	basic = vect_basic();
	central = vect_central(env);
	theta0 = theta(central) - theta(basic);
	free(basic);
	free(central);
	return (theta0);
}

void    change_vect(t_vect *v, float phi1, float theta1)
{
	float phi0;
	float theta0;
	float x;
	float y;
	float z;
	phi0 = phi(v);
	theta0 = theta(v);
	y = norm(v) * cos(phi0 + phi1);
	x = norm(v) * sin(phi0 + phi1) * sin(theta1 + theta0);
	z = norm(v) * sin(phi0 + phi1) * cos(theta1 + theta0);
    v->y= y;
    v->x = x;
    v->z = z;
	//return (new_vect(x, y, z));
}       

void    set_virtual_screen(t_env *env)
{
	t_vect *v;
	t_vect *n;
	t_vect *aver;
	t_vect *w;

	aver = center_average(env);
	v = minus_vect(aver, env->cam->pos);
	free(aver);
	n = normed_vect(v);
	free(v);
	v = multiply_scalar(n, 100);
	free(n);
	w = add_vect(env->cam->pos, v);
	if (!(env->screen = (t_screen*)malloc(sizeof(t_screen))))
		return ;
	env->screen->center = v;
	env->screen->v = vectv(n);
	env->screen->w = vectw(n);
}

t_hit_point         *(*get_obj_collider(int id))(void *o, t_ray *r)
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


t_light       *add_light(t_light *light, t_vect *pos)
{
	t_light *tmp;
	t_light *new;
	if (!light)
	{
		if (!(light = (t_light*)malloc(sizeof(t_light))))
			return (NULL);
		light->pos = pos;
		light->red = 255;
		light->green = 255;
		light->blue = 255;
		light->next = NULL;
	}
	else 
	{
		tmp = light;
		while (tmp->next)
			tmp = tmp->next;
		new = (t_light*)malloc(sizeof(t_light));
		new->pos = pos;
		new->red = 255;
		new->green = 255;
		new->blue = 255;
		new->next = NULL;
		tmp->next = new;
	}
	return (light);
}

t_obj       *add_obj(t_obj *obj, int obj_type, t_mater *mater, void *type)
{
	t_obj *tmp;
	t_obj  *new;
	if (!obj)
	{
		if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
			return (NULL);
		obj->is_hit = get_obj_collider(obj_type);
		obj->type = type;
		obj->form = obj_type;
		obj->mater = mater;
		obj->next = NULL;
	}
	else 
	{
		tmp = obj;
		while (tmp->next)
			tmp = tmp->next;
		new = (t_obj*)malloc(sizeof(t_obj));
		new->is_hit = get_obj_collider(obj_type);
		new->type = type;
		new->mater = mater;
		new->form = obj_type;
		new->next = NULL;
		tmp->next = new;
	}
	return (obj);
}

t_hit_point     *new_hit_point(t_vect *vect, float dist_to_cam, t_vect *normal, int form)
{
	t_hit_point *ht;
	if (!(ht = (t_hit_point*)malloc(sizeof(t_hit_point))))
		return (NULL);
	ht->vect = vect;
	ht->distance_to_cam = dist_to_cam;
	ht->normal = normal;
	ht->form = form;
	return (ht);
}

float       distance_with_cam(t_env *env, t_hit_point *hp)
{
	t_vect *diff;
	float dis;
	if (!hp)
		return (INFINI); 
	if (hp->distance_to_cam == -1.0)
		return (0.0);
	diff = minus_vect(env->cam->pos, hp->vect);
	dis = sqrt(pow(diff->x, 2) + pow(diff->y, 2) + pow(diff->z, 2));
	free(diff);
	return (dis);
}

t_ray   *new_ray(t_vect *orig, t_vect *dir, float fl, t_vect *color)
{
	t_ray *r;
	if (!(r = (t_ray*)malloc(sizeof(t_ray))))
		return (NULL);
	r->origin = orig;
	r->direction = dir;
	r->dist_to_screen = fl;
	r->color = color;
	return (r);
}

float       term(float alpha, float beta)
{
	return (2 * alpha * beta);
}
