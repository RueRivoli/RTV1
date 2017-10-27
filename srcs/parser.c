/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:18:02 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/26 13:30:28 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

t_vect			origin0(int to, void *o)
{
	t_vect		v;
	t_sphere	*sp;
	t_plan		*p;

	if (to == 1)
	{
		sp = (t_sphere*)o;
		v = sp->origin;
		return (v);
	}
	if (to == 2)
	{
		p = (t_plan*)o;
		v = p->origin;
		return (v);
	}
	return (vect_null());
}

t_vect			origin(int to, void *o)
{
	t_vect		v;
	t_vect		w;
	t_cylinder	*cyl;
	t_cone		*c;

	w = origin0(to, o);
	if (equals_vect(w, vect_null()))
	{
		if (to == 3)
		{
			cyl = (t_cylinder*)o;
			v = cyl->origin;
		}
		if (to == 4)
		{
			c = (t_cone*)o;
			v = c->summit;
		}
		return (v);
	}
	else
		return (w);
}

t_vect			normal(int to, void *o)
{
	t_vect		n;
	t_plan		*p;
	t_cylinder	*cyl;
	t_cone		*c;

	n = vect_null();
	if (to == 2)
	{
		p = (t_plan*)o;
		n = p->normal;
	}
	if (to == 3)
	{
		cyl = (t_cylinder*)o;
		n = cyl->normal;
	}
	if (to == 4)
	{
		c = (t_cone*)o;
		n = c->axis;
	}
	return (n);
}

int				start_reading(int fd, char *filip, t_env *env, int *index)
{
	char	*line;

	line = NULL;
	if (ft_strncmp(filip, "# Scene", 7) == 0)
	{
		(*index)++;
		get_next_line(fd, &line);
		free(line);
		if (*index != 1 || read_scene(fd, env) < 4)
			return (0);
		return (1);
	}
	return (0);
}

int				lecture(int fd, t_env *env)
{
	char	*line;
	int		index;

	index = 0;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (!line && index == 0)
			return (0);
		if (index == 0 && (start_reading(fd, line, env, &index) == 1))
		{
			free(line);
			return (ft_norm3(env, fd, &index));
		}
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	if (index < 2)
		return (0);
	return (1);
}
