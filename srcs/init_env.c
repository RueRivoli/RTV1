/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:10:26 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 18:06:03 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_env	*init_env(t_env *env)
{
	t_win	*win;

	/*if (!(env = malloc(sizeof(t_env))))
		return (NULL)*/
	if (!(env->win = malloc(sizeof(t_win))))	
		return (NULL);
	/*if (!(env->cam = malloc(sizeof(t_cam))))
		return (NULL);*/
	if (!(env->screen = malloc(sizeof(t_screen))))
		return (NULL);
	env->thread_cnt = NB_THREAD;
	env->obj = NULL;
	env->light = NULL;
	win = env->win;
	win->width = 0;
	win->height = 0;
	env->boucle = 0;
	env->x = 0;
	env->y = 0;
	env->z = 0;
	env->nb_of_lights = 0;
	return (env);
}
