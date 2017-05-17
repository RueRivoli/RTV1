#include "rtv1.h"

t_sphere    *new_sphere(t_vect *v1, float rad)
{
    t_sphere *v;
    if (!(v = (t_sphere*)malloc(sizeof(t_sphere))))
        return (NULL);
    v->origin = v1;
    v->radius = rad;
    return (v);
}

t_cam   *new_cam(t_vect *v1)
{
    t_cam *c;
    if (!(c = (t_cam*)malloc(sizeof(t_cam))))
        return (NULL);
    c->pos = v1;
    return (c);
}

t_ray   *new_ray(t_vect *orig, t_vect *dir)
{
    t_ray *r;
    if (!(r = (t_ray*)malloc(sizeof(t_ray))))
        return (NULL);
    r->origin = orig;
    r->direction = dir;
    return (r);
}

int         belong(t_sphere *sp, t_vect *v)
{
    float f;

    f = sqrt((v->x - sp->origin->x) * (v->x - sp->origin->x) + \
    (v->y - sp->origin->y) * (v->y - sp->origin->y) + (v->z - sp->origin->z) * (v->z - sp->origin->z));
    if (f < sp->radius)
        return (1);
    return (0);
}

int         hit_sphere(t_sphere *sp, t_ray *r)
{
    float t;
    t_vect *v;
    t_vect *w;
    t = 0.0;
    while (t < 1000.0)
    {
        v = new_vect(r->direction->x * t,r->direction->y * t, r->direction->z * t);
        w = add_vect(v, r->origin);
        if (belong(sp, w) == 1)
            return (1);
        t = t + 15.0;
    }
    return (0);
}
