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

int				is_transform(char *line)
{
	if ((ft_strncmp(line, "translationX", 12) == 0) || \
		(ft_strncmp(line, "translationY", 12) == 0) || \
		(ft_strncmp(line, "translationZ", 12) == 0) || \
		(ft_strncmp(line, "rotationX", 9) == 0) || \
		(ft_strncmp(line, "rotationY", 9) == 0) || \
		(ft_strncmp(line, "rotationZ", 9) == 0))
		return (1);
	else
		return (0);
}

int				ft_norm3(t_env *env, int fd, int *index)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (ft_strncmp(line, "# Objects", 9) == 0)
		{
			(*index)++;
			free(line);
			get_next_line(fd, &line);
			if (*index != 2 || read_objects(fd, env) == 0)
			{
				free(line);
				return (0);
			}
		}
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	if (*index != 2)
		return (0);
	return (1);
}

t_env			*init_env(t_env *env)
{
	t_win	*win;

	if (!(env->win = malloc(sizeof(t_win))))
		return (NULL);
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
