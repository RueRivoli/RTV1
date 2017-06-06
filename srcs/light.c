#include "rtv1.h"


float calcul(t_env *env, t_hit_point *hp)
{
    t_vect *v;
    float res;
    v = minus_vect(env->light->pos, hp->vect);
    v = normed_vect(v);
    res =  scalar_product(hp->normal, v);
  
    return (res); 
}

float       coef_lambert(t_light *light, t_hit_point *hp)
{
    t_vect *v;
    float res;
    
   /*if (hp->form == 4)
        v = multiply_scalar(normed_vect(minus_vect(env->light->pos, hp->vect)), -1.0);
    else */
        v = multiply_scalar(normed_vect(minus_vect(light->pos, hp->vect)), 1.0);
    //printf("v->x %f\n", v->x);
    //printf("v->y %f\n", v->y);
    //printf("v->z %f\n", v->z);
    //printf("hp->x %f\n", hp->normal->x);
    //printf("hp->y %f\n", hp->normal->y);
    //printf("hp->z %f\n", hp->normal->z);
    res = scalar_product(hp->normal, v);
    if (hp->form == 2)
        res = max(max(-res, res), 0.0);
    else
        res = max(res, 0.0);
    return (res);
}

t_vect      *find_color(t_light *light, t_hit_point *hp, t_mater *mat)
{
    t_vect *new_color;
    float lambert;

    lambert = coef_lambert(light, hp);
    new_color = new_vect((lambert * mat->ir * light->red) / (255) , (lambert * mat->ig * light->green) / (255), (lambert * mat->ib * light->blue) / (255));
    //new_color = new_vect((lambert * mat->ir * env->light->red + 0.1 * mat->ir * env->light->red) / (1.1 * 255) , (lambert * mat->ig * env->light->green + 0.1 * mat->ig * env->light->green) / (1.1 * 255), (lambert * mat->ib * env->light->blue + 0.1 * mat->ib * env->light->blue) / (1.1 * 255));
    return (new_color);
}

t_vect      *find_color_light(t_light *light, t_hit_point *hp, t_mater *mat, t_vect *v)
{
    t_vect *new_color;
    float lambert;

    lambert = coef_lambert(light, hp);
    new_color = new_vect((lambert * mat->ir * light->red) + v->x , (lambert * mat->ig * light->green) + v->y, (lambert * mat->ib * light->blue) + v->z);
    //new_color = new_vect((lambert * mat->ir * env->light->red + 0.1 * mat->ir * env->light->red) / (1.1 * 255) , (lambert * mat->ig * env->light->green + 0.1 * mat->ig * env->light->green) / (1.1 * 255), (lambert * mat->ib * env->light->blue + 0.1 * mat->ib * env->light->blue) / (1.1 * 255));
    return (new_color);
}

t_vect      *find_color_sha(t_light *light, t_hit_point *hp, t_mater *mat, t_vect *v)
{
    t_vect *new_color;
    float lambert;

    lambert = coef_lambert(light, hp);
    new_color = new_vect(((lambert * mat->ir * light->red) / 2) + v->x , (lambert * mat->ig * light->green / 2) + v->y, (lambert * mat->ib * light->blue / 2)+ v->z);
    //new_color = new_vect((lambert * mat->ir * env->light->red + 0.1 * mat->ir * env->light->red) / (1.1 * 255) , (lambert * mat->ig * env->light->green + 0.1 * mat->ig * env->light->green) / (1.1 * 255), (lambert * mat->ib * env->light->blue + 0.1 * mat->ib * env->light->blue) / (1.1 * 255));
    return (new_color);
}

int         numberoflights(t_env *env)
{
    int ct;
    t_light *light;
    ct = 0;
    light = env->light;
    while (light)
    {
        light = light->next;
        ct++;
    }
    return (ct);
}
