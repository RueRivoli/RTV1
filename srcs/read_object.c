#include "rtv1.h"
#include <stdio.h>


int         type_objects(char *str)
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

int        read_scene(int fd, char *line, t_env *env)
{
    int ret;

	ret = read_name(fd, line, env);
    ret += read_camera(fd, line, env);
	ret += read_render(fd, line, env);
    ret += read_spot(fd, line, env);
    return (ret);
}

t_vect      *read_origin(char *line, int fd, char *str)
{
	t_vect *vect;
	char **tab;
	char *st;
	st = ft_strstr(line, str);
	if (get_next_line(fd, &line) && (st = ft_strstr(line, str)))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1] && tab[2] && tab[3])
			vect = new_vect(ft_atoi(tab[1]), ft_atoi(tab[2]), ft_atoi(tab[3]));
		else
			return (NULL);
		free(tab);
		free(st);
	}
	else
		return (NULL);
	
	return (vect);
}


float   read_float(char *line, int fd, char *str)
{
	char **tab;
	float res;
	char *st;
	st = ft_strstr(line, str);
	if (get_next_line(fd, &line) && (st = ft_strstr(line, str)))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1])
			res = ft_atoi(tab[1]);
		else
			return (0);
		free(tab);
		free(st);
	}
	else
		return (0);
	//free(line);
	return (res);
}

t_mater      *read_mater(char *line, int fd, char *str)
{
	t_mater *mat;
	char **tab;
	char *st;
	st = ft_strstr(line, str);
	if (get_next_line(fd, &line) && (st = ft_strstr(line, str)))
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1] && tab[2] && tab[3] && tab[4] && ft_atoi(tab[1]) > -1 && ft_atoi(tab[2]) > -1 && ft_atoi(tab[1]) > -1 && ft_atoi(tab[4]) > -1)
			mat = new_mater(ft_atoi(tab[1]), ft_atoi(tab[2]), ft_atoi(tab[3]), ft_atoi(tab[4]));
		else
			return (NULL);
		free(tab);
		free(st);
	}
	else
		return (NULL);
	return (mat);
}
