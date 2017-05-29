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

int         belong_to_sphere(t_sphere *sp, t_vect *v)
{
    float f;

    f = sqrt((v->x - sp->origin->x) * (v->x - sp->origin->x) + \
    (v->y - sp->origin->y) * (v->y - sp->origin->y) + (v->z - sp->origin->z) * (v->z - sp->origin->z));
    if (f < sp->radius)
        return (1);
    return (0);
}

/*t_hit_point         *hit_sphere1(void *o, t_ray *r)
{
    float delta;
    float a;
    t_vect *vect;
    float res;
    t_sphere *sp;
    sp = (void *)o;
    delta = 2 * (r->origin->x * r->direction->x + r->origin->y * r->direction->y + r->origin->z * r->direction->z - (r->direction->x * sp->origin->x +\
    r->direction->y * sp->origin->y + r->direction->z * sp->origin->z));
    delta = pow(delta, 2);
    a = pow(r->direction->x, 2) + pow(r->direction->y, 2) + pow(r->direction->z, 2);
    
    a *= pow(r->origin->x, 2) + pow(r->origin->y, 2) + pow(r->origin->z, 2) + pow(sp->origin->x, 2) + pow(sp->origin->y, 2) + pow(sp->origin->z, 2) - 2 * (sp->origin->x * r->origin->x + sp->origin->y  * r->origin->y + sp->origin->z * r->origin->z) - pow(sp->radius, 2);
    delta = delta - 4 * a;
     
    if (delta > 0.0)
    {
        res = (- b - sqrt(delta)) / 2 * a;
        vect = new_vect(r->origin + res * r->direction->x, r->origin + res * r->direction->y, r->origin + res * r->direction->z);
        return (new_hit_point(vect, 0.0));
    }
    return (NULL);
}*/

t_hit_point         *hit_sphere(void *o, t_ray *r)
{
    float delta;
    float a;
    t_vect *vect;
    float res;
    t_sphere *sp;
    sp = (void *)o;
    float  b;
    float c;
    a = 1.0;
    b = 2 * ((r->origin->x - sp->origin->x) * r->direction->x +  (r->origin->y - sp->origin->y) * r->direction->y + (r->origin->z - sp->origin->z) * r->direction->z);
    c = pow(r->origin->x - sp->origin->x, 2) +  pow(r->origin->y - sp->origin->y, 2) + pow(r->origin->z - sp->origin->z, 2) - pow(sp->radius, 2);
    delta = pow(b, 2) - 4 * a * c;
    if (delta >= 0.0)
    {
        res = min_positiv((- b - sqrt(delta)) / (2 * a), (- b + sqrt(delta)) / (2 * a));
        if (res > 0)
        {
            vect = new_vect(r->origin->x + res * r->direction->x, r->origin->y + res * r->direction->y, r->origin->z + res * r->direction->z);
            return (new_hit_point(vect, 0.0));
        }
    }
    return (NULL);
}
