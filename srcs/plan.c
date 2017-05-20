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

int         hit_plan(t_plan *p, t_ray *r)
{
    float num;
    float den;

    num = scalar_product(p->normal, minus_vect(p->origin, r->origin));
    den = scalar_product(p->normal, r->direction);
    num /= den;
    if (num > 0)
    {
        return (1);
    } 
    return (0);
}
