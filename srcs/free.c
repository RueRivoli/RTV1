#include "rtv1.h"

void	free_ray(t_ray *ray)
{
	free(ray->origin);
	free(ray->direction);
	free(ray->color);
	free(ray);
}

void	free_hit_point(t_hit_point *hp)
{
	free(hp->vect);
	free(hp->normal);
	free(hp);
}


void	free_tab(char **tab)
{
	int i;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}
