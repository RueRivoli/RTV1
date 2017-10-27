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

int			read_objects(int fd, t_env *env)
{
	int		to;
	char	*str;
	char	*line;
	int		ret;

	ret = 0;
	to = 0;
	line = NULL;
	str = NULL;
	while (get_next_line(fd, &line))
	{
		ret += ft_norm(env, str, line, fd);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	return (ret);
}

int			read_name(int fd, t_env *env)
{
	char		*str;
	char		**tab;
	char		*line;
	int			ret;

	ret = 0;
	tab = NULL;
	line = NULL;
	if (get_next_line(fd, &line) && (ft_strncmp(line, "name", 4) == 0))
	{
		tab = ft_strsplit(line, ' ');
		if ((str = tab[1]))
		{
			env->title = str;
			ret++;
		}
		free_tab(tab);
	}
	free(line);
	return (ret);
}

int			read_camera(int fd, t_env *env)
{
	int			ret;
	char		**tab;
	t_vect		v;
	t_vect		trans;
	char		*line;

	ret = 0;
	v = vect_null();
	tab = NULL;
	trans = vect_null();
	line = NULL;
	if (get_next_line(fd, &line) && (ft_strncmp(line, "camera", 6) == 0))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[2] != NULL && tab[3] != NULL && tab[4] != NULL)
		{
			v = new_vect(ft_atof(tab[2]), ft_atof(tab[3]), ft_atof(tab[4]));
			ret++;
		}
		free_tab(tab);
		env->cam = new_cam(v, trans, 0.0, 0.0);
	}
	free(line);
	return (ret);
}

int			read_render(int fd, t_env *env)
{
	int		ret;
	char	**tab;
	char	*line;

	ret = 0;
	line = NULL;
	tab = NULL;
	if (get_next_line(fd, &line) && (ft_strncmp(line, "render", 6) == 0))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[2] != NULL && tab[3] != NULL)
		{
			env->screen->nx = ft_atoi(tab[2]);
			env->screen->ny = ft_atoi(tab[3]);
			ret++;
		}
		free_tab(tab);
	}
	free(line);
	return (ret);
}

int			read_spot(int fd, t_env *env)
{
	int		ret;
	char	*line;

	ret = 0;
	line = NULL;
	while (get_next_line(fd, &line) && (ft_strncmp(line, "spot", 4) == 0))
	{
		ret += ft_norm2(env, line);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	return (ret);
}
