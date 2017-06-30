#include "rtv1.h"
#include <stdio.h>

t_vect 				origin0(int to, void *o)
{
	t_vect v;
	if (to == 1)
	{   
		t_sphere *sp;
		sp = (t_sphere*)o;
		v = sp->origin;
		return (v);
	}
	if (to == 2)
	{   
		t_plan *p;
		p = (t_plan*)o;
		v = p->origin;
		return (v);
	}
	return (vect_null());
}

t_vect      		origin(int to, void *o)
{
	t_vect v;
	t_vect w;
	w = origin0(to, o);
	if (equals_vect(w, vect_null()))
	{
		if (to == 3)
		{   
			t_cylinder *cyl;
			cyl = (t_cylinder*)o;
			v = cyl->origin;
		}
		if (to == 4)
		{   
			t_cone *c;
			c = (t_cone*)o;
			v = c->summit;
		}
	
		return (v);
	}
	else
		return (w);
}

t_vect     		 normal(int to, void *o)
{
	t_vect n;
	n = vect_null();
	if (to == 2)
	{   
		t_plan *p;
		p = (t_plan*)o;
		n = p->normal;
	}
	if (to == 3)
	{   
		t_cylinder *cyl;
		cyl = (t_cylinder*)o;
		n = cyl->normal;
	}
	if (to == 4)
	{   
		t_cone *c;
		c = (t_cone*)o;
		n = c->axis;
	}
	return (n);
}



void		start_reading(int fd, char *line, t_env *env, int *index)
{
	char *st;
	if ((st = ft_strstr(line, "# Scene")))
	{
			*index += *index + 1;
			get_next_line(fd, &line);
			
			if (*index != 1 || read_scene(fd, line,env) < 3)
			{
				error_param();
				return;
			}
			
			//free(st);
	}
}	

int        lecture(int fd, t_env *env)
{
	char *line;
	char *st;
	int index;
	index = 0;
	
	while (get_next_line(fd, &line))
	{	
		start_reading(fd, line, env, &index);
		st = ft_strstr(line, "# Objects");
		if (st != NULL)
		{
			index++;
			get_next_line(fd, &line);
			if (index != 2 || read_objects(fd, line, env) == 0)
			{
				error_param();
				return (0);
			}
			//free(st);
		}
		//free(line);
	}
	if (index < 2)
	{
		error_param();
		return (0);
	}
	return (1);
}
