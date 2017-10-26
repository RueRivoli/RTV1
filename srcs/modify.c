/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 16:05:26 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 18:24:25 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		translation(char *line, void *o, int to)
{
	char			**tab;

	tab = NULL;
	if ((ft_strncmp(line, "translationX", 12) == 0))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
			apply_trans(to, o, ft_atof(tab[1]), 1);
		free_tab(tab);
	}
	if ((ft_strncmp(line, "translationY", 12) == 0))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
			apply_trans(to, o, ft_atof(tab[1]), 2);
		free_tab(tab);
	}
	if ((ft_strncmp(line, "translationZ", 12) == 0))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
			apply_trans(to, o, ft_atof(tab[1]), 3);
		free_tab(tab);
	}
}

void		rotation(char *line, void *o, int to)
{
	char		**tab;
	t_vect		n;
	float		theta;

	n = normal(to, o);
	tab = NULL;
	if ((ft_strncmp(line, "rotationX", 9) == 0) && to != 1)
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
		{
			theta = ft_atof(tab[1]) * M_PI / 180;
			normed(&n);
			apply_rotate(to, o, theta, 1);
		}
		free_tab(tab);
	}
	rotation_y(line, o, to);
	rotation_z(line, o, to);
}

void		rotation_y(char *line, void *o, int to)
{
	char		**tab;
	t_vect		n;
	float		theta;

	n = normal(to, o);
	tab = NULL;
	if ((ft_strncmp(line, "rotationY", 9) == 0) && to != 1)
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
		{
			theta = ft_atof(tab[1]) * M_PI / 180;
			normed(&n);
			apply_rotate(to, o, theta, 2);
		}
		free_tab(tab);
	}
}

void		rotation_z(char *line, void *o, int to)
{
	char		**tab;
	t_vect		n;
	float		theta;

	n = normal(to, o);
	tab = NULL;
	if ((ft_strncmp(line, "rotationZ", 9) == 0) && to != 1)
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
		{
			theta = ft_atof(tab[1]) * M_PI / 180;
			normed(&n);
			apply_rotate(to, o, theta, 3);
		}
		free_tab(tab);
	}
}

void		modify(void *o, int fd, int to)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		if ((ft_strncmp(line, "translationX", 12) == 0) || \
			(ft_strncmp(line, "translationY", 12) == 0) || \
			(ft_strncmp(line, "translationZ", 12) == 0) || \
			(ft_strncmp(line, "rotationX", 9) == 0) || \
			(ft_strncmp(line, "rotationY", 9) == 0) || \
			(ft_strncmp(line, "rotationZ", 9) == 0))
		{
			if (to)
			{
				translation(line, o, to);
				rotation(line, o, to);
			}
			free(line);
		}
		else
		{
			free(line);
			break ;
		}
	}
}
