/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 16:01:33 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 16:02:10 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_sin(char *s)
{
	if (s != NULL)
		free(s);
}

void	free_mult(char *st, char *st2)
{
	if (st != NULL)
		free(st);
	if (st2 != NULL)
		free(st2);
}

void	free_light(t_light *light)
{
	t_light *l;
	t_light *tmp;
	l = light;
	while (l)
	{
		tmp = l;
		free(tmp);
		l = l->next;
	}
}

void	free_obj(t_obj *obj)
{
	t_obj *object;
	t_obj *tmp;

	object = obj;
	while (object)
	{
		tmp = object;
		free(tmp);
		object = object->next;
	}
}

void	free_env(t_env *env)
{
	if (env)
	{
		if (env->win)
		 	free(env->win);
		if (env->screen)
		 	free(env->screen);
		if (env->cam)
			free(env->cam);
		if (env->light)
		  	free_light(env->light);
		if (env->obj)
			 free(env->obj);
		if (env->thread)
			free(env->thread);
		free(env);
	}
}
