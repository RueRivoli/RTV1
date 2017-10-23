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
	char			*st;

	tab = NULL;
	if ((st = ft_strstr(line, "translationX")))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
			apply_trans(to, o, ft_atof(tab[1]), 1);
		free_tab(tab);
		free(st);
	}
	if ((st = ft_strstr(line, "translationY")))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
			apply_trans(to, o, ft_atof(tab[1]), 2);
		free_tab(tab);
		free(st);
	}
	if ((st = ft_strstr(line, "translationZ")))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
			apply_trans(to, o, ft_atof(tab[1]), 3);
		free_tab(tab);
		free(st);
	}
}

void		rotation(char *line, void *o, int to)
{
	char		**tab;
	t_vect		n;
	char		*st;
	float		theta;

	n = normal(to, o);
	tab = NULL;
	
	if ((st = ft_strstr(line, "rotationX")) && to != 1)
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
		{
			theta = ft_atof(tab[1]) * M_PI / 180;
			normed(&n);
			apply_rotate(to, o, theta, 1);
		}
		free_tab(tab);
		free(st);
		
	}
	rotation_y(line, o, to);
	rotation_z(line, o, to);
}

void		rotation_y(char *line, void *o, int to)
{
	char		**tab;
	t_vect		n;
	char		*st;
	float		theta;

	n = normal(to, o);
	tab = NULL;
	if ((st = ft_strstr(line, "rotationY")) && to != 1)
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
		{
			theta = ft_atof(tab[1]) * M_PI / 180;
			normed(&n);
			apply_rotate(to, o, theta, 2);
		}
		free_tab(tab);
		free(st);
	}
	
}

void		rotation_z(char *line, void *o, int to)
{
	char		**tab;
	t_vect		n;
	char		*st;
	float		theta;

	n = normal(to, o);
	tab = NULL;
	if ((st = ft_strstr(line, "rotationZ")) && to != 1)
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
		{
			theta = ft_atof(tab[1]) * M_PI / 180;
			normed(&n);
			apply_rotate(to, o, theta, 3);
		}
		free_tab(tab);
		free(st);
	}
}

void		modify(void *o, char *line, int fd, int to)
{
	char		*st;
	char		*st1;
	char		*st2;
	char		*st3;
	char		*st4;

	while (get_next_line(fd, &line) && ((st = ft_strstr(line, \
			"translationX")) || (st1 = ft_strstr(line, "translationY")) || \
				(st2 = ft_strstr(line, "translationZ")) || \
				(st3 = ft_strstr(line, \
				"rotationX")) || (st4 = ft_strstr(line, "rotationY")) || \
				(ft_strstr(line, "rotationZ"))))
	{
		/*free_mult(st, st1);
		free_mult(st2, st3);*/
		if (to)
		{
			translation(line, o, to);
			rotation(line, o, to);
		}
	}
	
	
}
