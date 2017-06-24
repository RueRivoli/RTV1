#include "rtv1.h"


void    translation(char *line, void *o, int to)
{
    char **tab;
    t_vect *v;
	v = origin(to, o);
    tab = NULL;
	char *st;
    if ((st = ft_strstr(line, "translationX")))
		{
			tab = ft_strsplit(line, ' ');
			if (tab[1])
				v->x += ft_atoi(tab[1]);
				free(tab);
				free(st);
		}
		if ((st = ft_strstr(line, "translationY")))
		{
			tab = ft_strsplit(line, ' ');
			if (tab[1])
				v->y += ft_atoi(tab[1]);
				free(tab);
				free(st);
		}
		if ((st = ft_strstr(line, "translationZ")))
		{
			tab = ft_strsplit(line, ' ');
			if (tab[1])
				v->z += ft_atoi(tab[1]);
			free(tab);
			free(st);
		}
}

void    rotation(char *line, void *o, int to)
{
    char **tab;
    t_vect *n;
    float mem;
    float theta;
	n = normal(to, o);
    tab = NULL;
    if (ft_strstr(line, "rotationX") && to != 1)
		{
			tab = ft_strsplit(line, ' ');
			if (tab[1])
			{
				theta = ft_atoi(tab[1]) * M_PI / 180;
				mem = n->y;
				n->y = cos(theta) * n->y + sin(theta) * n->z;
				n->z = -sin(theta) * mem + cos(theta) * n->z;
				normed(n);
				//printf("%.2f %.2f", p->normal->y, p->normal->z);
			}
			free(tab);
		}
		rotation_Y(line, o, to);
        rotation_Z(line, o, to);
}

void        rotation_Y(char *line, void *o, int to)
{
     char **tab;
    t_vect *n;
    float mem;
    float theta;
	n = normal(to, o);
    tab = NULL;
    if (ft_strstr(line, "rotationY") && to != 1)
		{
			tab = ft_strsplit(line, ' ');
			if (tab[1])
			{
				theta = ft_atoi(tab[1]) * M_PI / 180;
				mem = n->x;
				n->x = cos(theta) * n->x + sin(theta) * n->z;
				n->z = -sin(theta) * mem + cos(theta) * n->z;
				normed(n);
			}
			free(tab);
		}
}

void        rotation_Z(char *line, void *o, int to)
{
    char **tab;
    t_vect *n;
    float mem;
    float theta;
	n = normal(to, o);
    tab = NULL;
    if (ft_strstr(line, "rotationZ") && to != 1)
		{
			tab = ft_strsplit(line, ' ');
			if (tab[1])
			{
				theta = ft_atoi(tab[1]) * M_PI / 180;
				mem = n->x;
				n->x = cos(theta) * n->x + sin(theta) * n->y;
				n->y = -sin(theta) * mem + cos(theta) * n->y;
				normed(n);
			}
			free(tab);
		}
}

void        modify(void *o, char *line, int fd, int to)
{
	while (get_next_line(fd, &line) && (ft_strstr(line, "translationX") || ft_strstr(line, "translationY") || \
				ft_strstr(line, "translationZ") || ft_strstr(line, "rotationX") || ft_strstr(line, "rotationY") || \
				ft_strstr(line, "rotationZ")))
	{
		translation(line, o, to);
        rotation(line, o, to);
	}
}
