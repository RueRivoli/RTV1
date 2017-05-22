#include "rtv1.h"

t_plan  *new_plan(t_vect *origin, t_vect *normal)
{
    t_plan      *plan;

    if (!(plan = (t_plan *)malloc(sizeof(t_plan))))
        return (NULL);
    plan->origin = origin;
    plan->normal = normal;
    return (plan);
}

int         belong_to_plan(t_plan *p, t_vect *v)
{
    t_vect  *v1;
    v1 = minus_vect(v, p->origin);
    if (scalar_product(v1, p->normal) == 0.0)
        return (1);
    return (0);
}

t_hit_point         *hit_plan(void *o, t_ray *r)
{
    float den;
    float res;
    t_vect *v;
    t_plan *p;
    p = (t_plan *)o;
    res = scalar_product(p->normal, minus_vect(p->origin, r->origin));
    den = scalar_product(p->normal, r->direction);
    res /= den;
    if (res >= 0)
    {
        v = new_vect(r->origin->x + res * r->direction->x, r->origin->y + res * r->direction->y, r->origin->z + res * r->direction->z);
        return (new_hit_point(v, 0.0));
    } 
    return (NULL);
}
