/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:47:32 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/26 13:31:32 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <pthread.h>

int				ft_norm2(t_env *env, char *line)
{
	char		**tab;
	int			ret;

	ret = 0;
	tab = ft_strsplit(line, ' ');
	if (tab[1] && tab[2] && tab[3])
	{
		env->light = add_light(env->light, new_vect(ft_atof(tab[1]), \
		ft_atof(tab[2]), ft_atof(tab[3])));
		ret++;
	}
	free_tab(tab);
	free(line);
	return (ret);
}

int				thread_function(void *addr)
{
	t_arg		*arg;
	int			pmin;
	int			pmax;

	arg = (t_arg *)addr;
	pmin = (int)(arg->i * (arg->env->screen->nx / NB_THREAD));
	pmax = (int)((arg->i + 1) * (arg->env->screen->nx / NB_THREAD));
	raytrace_thread(arg->env, pmin, pmax);
	return (1);
}

void			fill_arg(t_arg *arg, void *a)
{
	int ct;

	ct = 0;
	while (ct < NB_THREAD)
	{
		arg[ct].env = a;
		arg[ct].i = ct;
		ct++;
	}
	return ;
}

void			boucle(t_arg *arg, t_env *env)
{
	SDL_Thread		*testthread;
	int				ct;

	fill_arg(arg, env);
	ct = 0;
	while (ct < NB_THREAD)
	{
		testthread = SDL_CreateThread(thread_function, \
				"Thread", (void*)&arg[ct]);
		SDL_WaitThread(testthread, NULL);
		ct++;
	}
}
