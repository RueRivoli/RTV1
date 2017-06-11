#include "rtv1.h"


void        display_camera(t_env *env)
{
    t_vect *camera;
    camera = env->cam->pos;
	ft_putstr("Cadre \n\n");
	ft_putstr(env->title);
	ft_putstr("\n");
	ft_putstr("Camera : ");
	ft_putnbr(camera->x);
	ft_putstr(", ");
	ft_putnbr(camera->y);
	ft_putstr(", ");
	ft_putnbr(camera->z);
	ft_putstr("\n");
	ft_putstr("Taille : ");
	ft_putnbr(env->size_x);
	ft_putstr(" ");
	ft_putnbr(env->size_y);
	ft_putstr("\n");
}

void        display_light(t_env *env)
{
    t_light *light;
    light = env->light;
    ft_putstr("Light : ");
	while (light)
	{
		ft_putnbr(light->pos->x);
		ft_putstr(", ");
		ft_putnbr(light->pos->y);
		ft_putstr(", ");
		ft_putnbr(light->pos->z);
		ft_putstr("\n");
		light = light->next;
	}
	ft_putstr("\n\n");
}

void        display_sphere(t_sphere *sp, t_mater *mat)
{
    ft_putstr("Sphere \n");
	ft_putstr("Centre : ");
	ft_putnbr(sp->origin->x);
	ft_putstr(", ");
	ft_putnbr(sp->origin->y);
	ft_putstr(", ");
	ft_putnbr(sp->origin->z);
	ft_putstr("\n");
	ft_putstr("Radius : ");
	ft_putnbr(sp->radius);
	ft_putstr("\n");
	display_mat(mat);
}

void        display_mat(t_mater *mat)
{
    ft_putstr("Color : ");
    ft_putnbr(mat->alpha);
	//printf("%f", mat->alpha);
	ft_putstr(", ");
    ft_putnbr(mat->ir);
	ft_putstr(", ");
	ft_putnbr(mat->ig);
	ft_putstr(", ");
	ft_putnbr(mat->ib);
	ft_putstr("\n");
}

void        display_plan(t_plan *p, t_mater *mat)
{
    ft_putstr("Plan \n");
	ft_putstr("Origin : ");
	ft_putnbr(p->origin->x);
	ft_putstr(", ");
	ft_putnbr(p->origin->y);
	ft_putstr(", ");
	ft_putnbr(p->origin->z);
	ft_putstr("\n");
	ft_putstr("Normal : ");
	ft_putnbr(p->normal->x);
	ft_putstr(", ");
	ft_putnbr(p->normal->y);
	ft_putstr(", ");
	ft_putnbr(p->normal->z);
    ft_putstr("\n");
	display_mat(mat);
}
