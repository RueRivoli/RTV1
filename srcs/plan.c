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
    t_vect *essai;
    t_plan *p;
    p = (t_plan *)o;
    res = scalar_product(p->normal, minus_vect(p->origin, r->origin));
    den = scalar_product(p->normal, r->direction);
    if (den == 0.0)
    {
        printf(" valeurs oa %f\n", scalar_product(minus_vect(p->origin, r->origin), p->normal));
        if (scalar_product(minus_vect(p->origin, r->origin), p->normal) == 0.0)
        {
            v = new_vect(r->origin->x, r->origin->y, r->origin->z);
             return (new_hit_point(v, 0.0, normed_vect(p->normal)));
        }
    }
    else if (fabsf(den) > 1e-6)
    {
        res /= den;
        //res -= 0.0001;
        v = new_vect(r->origin->x + res * r->direction->x, r->origin->y + res * r->direction->y, r->origin->z + res * r->direction->z);
        essai = minus_vect(v, r->origin);
        if (res > 0.0 /*&& norm(essai) > 5*/)
        {
             return (new_hit_point(v, 0.0, normed_vect(p->normal)));
            
        }
    } 
    return (NULL);
}
