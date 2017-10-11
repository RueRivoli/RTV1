/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:29:00 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 17:32:39 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			read_objects(int fd, char *line, t_env *env)
{
	int		to;
	char	*str;
	char	**tab;
	char	*st;
	int		ret;

	ret = 1;
	to = 0;
	while (get_next_line(fd, &line) && ret)
	{
		tab = ft_strsplit(line, ' ');
		if ((st = ft_strstr(line, "name")) && \
				(str = tab[1]))
		{
			to = type_objects(str);
			if (to < 1 || to > 4)
				return (0);
			ret = registering(to, line, env, fd);
		}
	}
	return (ret);
}

int			read_name(int fd, char *line, t_env *env)
{
	char		*str;
	char		**tab;
	char		*st;
	int			ret;

	ret = 0;
	tab = NULL;
	if (get_next_line(fd, &line) && (st = ft_strstr(line, "name")))
	{
		tab = ft_strsplit(line, ' ');
		if ((str = tab[1]))
		{
			env->title = str;
			ret++;
		}
	}
	return (ret);
}

int			read_camera(int fd, char *line, t_env *env)
{
	int			ret;
	char		**tab;
	t_vect		v;
	t_vect		trans;
	char		*st;

	ret = 0;
	v = vect_null();
	tab = NULL;
	trans = vect_null();
	if (get_next_line(fd, &line) && (st = ft_strstr(line, "camera")))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[2] != NULL && tab[3] != NULL && tab[4] != NULL)
		{
			v = new_vect(ft_atof(tab[2]), ft_atof(tab[3]), ft_atof(tab[4]));
			ret++;
		}
		env->cam = new_cam(v, trans, 0.0, 0.0);
		ret++;
	}
	return (ret);
}

int			read_render(int fd, char *line, t_env *env)
{
	int		ret;
	char	**tab;
	char	*st;

	ret = 0;
	if (get_next_line(fd, &line) && (st = ft_strstr(line, "render")))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[2] != NULL && tab[3] != NULL)
		{
			env->screen->nx = ft_atoi(tab[2]);
			env->screen->ny = ft_atoi(tab[3]);
			env->win->height = ft_atoi(tab[3]);
			env->win->width = ft_atoi(tab[2]);
			ret++;
		}
	}
	return (ret);
}

int			read_spot(int fd, char *line, t_env *env)
{
	int		ret;
	char	**tab;
	char	*st;

	tab = NULL;
	ret = 0;
	while (get_next_line(fd, &line) && (st = ft_strstr(line, "spot")))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1] && tab[2] && tab[3])
		{
			env->light = add_light(env->light, new_vect(ft_atof(tab[1]), \
			ft_atof(tab[2]), ft_atof(tab[3])));
			ret++;
		}
	}
	return (ret);
}
