#include "rtv1.h"

t_vect      vectv(t_vect n)
{
	float x;
	float y;
	float z;
	t_vect v;
	x = 1.0;
	y = -n.x /n.y;
	z = 0.0;
	v = new_vect(x, y, z);
	normed(v);
	return (v);
}

t_vect      vectw(t_vect n)
{
	float x;
	float y;
	float z;
	t_vect v;
	t_vect w;
	y = -0.5 * n.z / (n.y + pow(n.x, 2)/ n.y);
	x = (n.x / n.z) * y;
	z = 0.5;
	v = new_vect(x, y, z);
	w = normed(v);
	//free(v);
	return (w);
}

void    set_virtual_screen(t_env *env)
{
	t_vect v;
	t_vect n;
	t_vect aver;
	t_vect w;

	aver = center_average(env);
	v = min_vect(aver, env->cam->pos);
	//free(aver);
	n = normed(v);
	//free(v);
	v = multiply_scalar(n, 100);
	//free(n);
	w = add_vect(env->cam->pos, v);
	if (!(env->screen = (t_screen*)malloc(sizeof(t_screen))))
		return ;
	env->screen->center = v;
	env->screen->v = vectv(n);
	env->screen->w = vectw(n);
}
