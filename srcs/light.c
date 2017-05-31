#include "rtv1.h"

float       coef_lambert(t_env *env, t_hit_point *hp)
{
    t_vect *v;
    float res;

    v = normed_vect(minus_vect(env->light->pos, hp->vect));
    
    res =  scalar_product(hp->normal, v);
    res = max(res, 0.0);
    return (res);
}

t_vect      *find_color(t_env *env, t_hit_point *hp, t_mater *mat)
{
    t_vect *new_color;
    float lambert;

 
    lambert = coef_lambert(env, hp);
    
    new_color = new_vect(lambert * mat->ir * env->light->red, lambert * mat->ig * env->light->green, lambert * mat->ir * env->light->blue);
    return (new_color);
}

