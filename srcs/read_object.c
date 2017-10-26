/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:32:47 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 17:34:57 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int			type_objects(char *str)
{
	if (ft_strcmp(str, "sphere") == 0)
		return (1);
	if (ft_strcmp(str, "plan") == 0)
		return (2);
	if (ft_strcmp(str, "cylinder") == 0)
		return (3);
	if (ft_strcmp(str, "cone") == 0)
		return (4);
	return (0);
}

int			read_scene(int fd, t_env *env)
{
	int		ret;

	ret = read_name(fd, env);
	ret += read_camera(fd, env);
	ret += read_render(fd, env);
	ret += read_spot(fd, env);
	return (ret);
}

t_vect		read_origin(int fd, char *str)
{
	t_vect		vect;
	char		**tab;
	char		*line;

	line = NULL;
	if (get_next_line(fd, &line) && \
		(ft_strncmp(line, str, ft_strlen(str)) == 0))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1] && tab[2] && tab[3])
			vect = new_vect(ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3]));
		else
			return (vect_null());
		free_tab(tab);
		free(line);
	}
	else
		return (vect_null());
	return (vect);
}

float		read_float(int fd, char *str)
{
	char		**tab;
	float		res;
	char		*line;

	line = NULL;
	if (get_next_line(fd, &line) && \
		(ft_strncmp(line, str, ft_strlen(str)) == 0))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
			res = ft_atof(tab[1]);
		else
		{
			free(line);
			return (0);
		}
		free_tab(tab);
		free(line);
	}
	else
		return (0);
	return (res);
}

t_mater		*read_mater(int fd, char *str)
{
	t_mater		*mat;
	char		**tab;
	char		*line;

	line = NULL;
	if (get_next_line(fd, &line) && \
		(ft_strncmp(line, str, ft_strlen(str)) == 0))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1] && tab[2] && tab[3] && tab[4] && ft_atof(tab[1]) > -1 \
				&& ft_atof(tab[2]) > -1 && ft_atof(tab[1]) > -1 && \
				ft_atof(tab[4]) > -1)
			mat = new_mater(ft_atof(tab[1]), ft_atof(tab[2]), \
					ft_atof(tab[3]), ft_atof(tab[4]));
		else
			return (NULL);
		free_tab(tab);
		free(line);
	}
	else
		return (NULL);
	return (mat);
}
