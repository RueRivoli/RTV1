/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:42:33 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/26 13:30:44 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <pthread.h>

pthread_t			**malloc_thread(int count, t_arg *arg, void *a)
{
	pthread_t		**thread;

	thread = (pthread_t **)malloc(sizeof(pthread_t *) * (count + 1));
	thread[count] = NULL;
	while (--count != -1)
	{
		thread[count] = (pthread_t *)malloc(sizeof(pthread_t));
		arg[count].env = a;
		arg[count].i = count;
	}
	return (thread);
}

static void			*thread_fonc(void *b)
{
	t_arg		*arg;
	int			pmin;
	int			pmax;

	arg = (t_arg *)b;
	pmin = (int)(arg->i * (arg->env->size_x / NB_THREAD));
	pmax = (int)((arg->i + 1) * (arg->env->size_x / NB_THREAD));
	raytrace_thread(arg->env, pmin, pmax);
	pthread_exit(NULL);
}

static void			create_thread(pthread_t **thread, int count, t_arg *arg)
{
	int			ret;

	while (--count != -1)
	{
		ret = pthread_create(thread[count], NULL,
			thread_fonc, &arg[count]);
	}
}

void				redraw(t_env *env, t_arg *arg)
{
	int		i;
	void	*ret;

	i = -1;
	create_thread(env->thread, env->thread_cnt, arg);
	while (env->thread[++i])
	{
		pthread_join(*env->thread[i], &ret);
	}
}
