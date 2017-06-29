#include "rtv1.h"

void        display_cylinder(t_cylinder *cyl, t_mater *mat)
{
    ft_putstr("Cylinder \n");
	ft_putstr("Origin : ");
	ft_putnbr(cyl->origin.x);
	ft_putstr(", ");
	ft_putnbr(cyl->origin.y);
	ft_putstr(", ");
	ft_putnbr(cyl->origin.z);
	ft_putstr("\n");
	ft_putstr("Normal : ");
	ft_putnbr(cyl->normal.x);
	ft_putstr(", ");
	ft_putnbr(cyl->normal.y);
	ft_putstr(", ");
	ft_putnbr(cyl->normal.z);
	ft_putstr("\n");
	ft_putstr("Radius : ");
	ft_putnbr(cyl->radius);
	ft_putstr("\n");
    display_mat(mat);
}

void        display_cone(t_cone *cone, t_mater *mat)
{
    ft_putstr("Cone \n");
	ft_putstr("Summit : ");
	ft_putnbr(cone->summit.x);
	ft_putstr(", ");
    ft_putnbr(cone->summit.y);
	ft_putstr(", ");
	ft_putnbr(cone->summit.z);
	ft_putstr("\n");
	ft_putstr("Axis : ");
	ft_putnbr(cone->axis.x);
	ft_putstr(", ");
	ft_putnbr(cone->axis.y);
	ft_putstr(", ");
	ft_putnbr(cone->axis.z);
	ft_putstr("\n");
	ft_putstr("Angle : ");
	ft_putnbr(cone->angle * 180 / M_PI);
	ft_putstr("\n");
	display_mat(mat);
}

void        accord_to_form(t_obj *obj, t_mater *mat)
{
    t_sphere *sp;
	t_plan *p;
    t_cylinder *cyl;
	t_cone *cone;
    if (obj->form == 1)
	{   
		sp = (t_sphere*)(obj->type);
		display_sphere(sp, mat);
	}
	if (obj->form == 2)
	{  
		p = (t_plan*)(obj->type);
		display_plan(p, mat);
	}
	if (obj->form == 3)
	{  
		cyl = (t_cylinder*)(obj->type);
          display_cylinder(cyl, mat);
	}
	if (obj->form == 4)
	{  
		cone = (t_cone*)(obj->type);
      display_cone(cone, mat);
	}
}

void        display_scene(t_env *env)
{
	t_obj *obj;
	t_mater *mat;

	obj = env->obj;
	display_camera(env);
    display_light(env);
	ft_putstr("Objects \n\n");
	while (obj)
	{
		mat = obj->mater;
		accord_to_form(obj, mat);
		obj = obj->next;
		ft_putchar('\n');
	}
}

