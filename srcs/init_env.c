/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:10:26 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/09 11:51:48 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_env   *init_env(t_arg *arg)
{
	t_env   *env;
	t_win   *win;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	if (!(env->win = malloc(sizeof(t_win))))
		return (NULL);
	if (!(env->cam = malloc(sizeof(t_cam))))
		return (NULL);	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
		return (NULL);
	env->thread_cnt = 8;
	//env->arg = (t_arg*)malloc(sizeof(t_arg) * env->threat_cnt);
	if (!(env->thread = malloc_thread(env->thread_cnt, arg, &env)))
			return (NULL);
	env->obj = NULL;
	env->light = NULL;
	env->screen = NULL;
	win = env->win;
	win->width = 0;
	win->height = 0;
	env->boucle = 0;
	env->x = 0;
	env->y = 0;
	env->z = 0;
	env->cam = NULL;
	return (env);
}
