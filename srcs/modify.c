/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 16:05:26 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 16:25:51 by fgallois         ###   ########.fr       */
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
			class(to, o, ft_atof(tab[1]), 1);
	}
	if ((st = ft_strstr(line, "translationY")))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
			class(to, o, ft_atof(tab[1]), 2);
	}
	if ((st = ft_strstr(line, "translationZ")))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
			class(to, o, ft_atof(tab[1]), 3);
	}
}

void		rotation(char *line, void *o, int to)
{
	char		**tab;
	t_vect		n;
	char		*st;
	float		mem;
	float		theta;

	n = normal(to, o);
	tab = NULL;
	if ((st = ft_strstr(line, "rotationX")) && to != 1)
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
		{
			theta = ft_atof(tab[1]) * M_PI / 180;
			/*mem = n.y;
			n.y = cos(theta) * n.y + sin(theta) * n.z;
			n.z = -sin(theta) * mem + cos(theta) * n.z;
			normed(&n);*/
			n = add_vect_rotation(n, theta, 1);
		}
		//free(tab);
		//free(st);
	}
	rotation_y(line, o, to);
	rotation_z(line, o, to);
}

void		rotation_y(char *line, void *o, int to)
{
	char		**tab;
	t_vect		n;
	char		*st;
	float		mem;
	float		theta;

	n = normal(to, o);
	tab = NULL;
	if ((st = ft_strstr(line, "rotationY")) && to != 1)
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
		{
			theta = ft_atof(tab[1]) * M_PI / 180;
			/*mem = n.x;
			n.x = cos(theta) * n.x + sin(theta) * n.z;
			n.z = -sin(theta) * mem + cos(theta) * n.z;
			normed(&n);*/
			n = add_vect_rotation(n, theta, 2);
		}
		//free(tab);
		//free(st);
	}
}

void		rotation_z(char *line, void *o, int to)
{
	char		**tab;
	t_vect		n;
	char		*st;
	float		mem;
	float		theta;

	n = normal(to, o);
	tab = NULL;
	if ((st = ft_strstr(line, "rotationZ")) && to != 1)
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
		{
			theta = ft_atof(tab[1]) * M_PI / 180;
			/*mem = n.x;
			n.x = cos(theta) * n.x + sin(theta) * n.y;
			n.y = -sin(theta) * mem + cos(theta) * n.y;
			normed(&n);*/
			n = add_vect_rotation(n, theta, 3);
		}
	}
}

void		modify(void *o, char *line, int fd, int to)
{
	char		*st;
	char		*st1;
	char		*st2;
	char		*st3;
	char		*st4;
	char		*st5;
	//ft_putstr("ALORS");
	while (get_next_line(fd, &line) && ((st = ft_strstr(line, \
	"translationX")) || (st1 = ft_strstr(line, "translationY")) || \
	(st2 = ft_strstr(line, "translationZ")) || \
	(st3 = ft_strstr(line, \
			"rotationX")) || (st4 = ft_strstr(line, "rotationY")) || \
	(st5 = ft_strstr(line, "rotationZ"))))
	{
		if (to)
		translation(line, o, to);
		rotation(line, o, to);
		/*free(st);
		free(st1);
		free(st2);
		free(st3);
		free(st4);
		free(st5);*/
	}
}
