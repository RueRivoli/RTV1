#include "rtv1.h"

t_cylinder  *new_cylinder(t_vect *origin, t_vect *normal, float radius)
{
    t_cylinder      *cyl;

    if (!(cyl = (t_cylinder *)malloc(sizeof(t_cylinder))))
        return (NULL);
    cyl->origin = origin;
    cyl->normal = normed_vector(normal); 
    cyl->radius = radius;
    return (cyl);
}

int         belong_to_cylinder(t_cylinder *c, t_vect *v)
{
    t_vect  *v1;

    v1 = minus_vect(v, c->origin);
    if (distance(v, add_vect(c->origin, multiply_scalar(normed_vector(c->normal), scalar_product(v, normed_vector(c->normal))))) <= c->radius)
        return (1);
    return (0);
}

float       alpha_cylinder(float expr, float n, float dir)
{
    return (n * expr - dir);
}

float       beta_cylinder(float expr2, float n, float a, float o)
{
    return (n * expr2 + o - a);
}

t_hit_point         *hit_cylinder(void *o, t_ray *r)
{
    float a;
    float b;
    float c;
    float expr;
    float expr2;
    float delta;
    float res;
    t_vect *v;
    t_cylinder *cyl;

    cyl = (t_cylinder*)o;

    expr = cyl->normal->x * r->direction->x + cyl->normal->y * r->direction->y + cyl->normal->z * r->direction->z;
    expr2 = (r->origin->x - cyl->origin->x) * cyl->normal->x + (r->origin->y - cyl->origin->y) * cyl->normal->y +\
    (r->origin->z - cyl->origin->z) * cyl->normal->z;
    a =  pow(alpha_cylinder(expr, cyl->normal->x, r->direction->x), 2) + pow(alpha_cylinder(expr, cyl->normal->y, r->direction->y), 2) +\
    pow(alpha_cylinder(expr, cyl->normal->z, r->direction->z), 2);
    b = term(alpha_cylinder(expr, cyl->normal->x, r->direction->x), beta_cylinder(expr2, cyl->normal->x, r->origin->x, cyl->origin->x))+\
    term(alpha_cylinder(expr, cyl->normal->y, r->direction->y), beta_cylinder(expr2, cyl->normal->y, r->origin->y, cyl->origin->y))+\
    term(alpha_cylinder(expr, cyl->normal->z, r->direction->z), beta_cylinder(expr2, cyl->normal->z, r->origin->z, cyl->origin->z));
    c = pow(beta_cylinder(expr2, cyl->normal->x, r->origin->x, cyl->origin->x), 2) +\
    pow(beta_cylinder(expr2, cyl->normal->y, r->origin->y, cyl->origin->y), 2) +\
    pow(beta_cylinder(expr2, cyl->normal->z, r->origin->z, cyl->origin->z), 2) - pow(cyl->radius, 2);
    delta = pow(b, 2) - 4 * a * c;
    if (delta >= 0)
    {
        res = (- b - sqrt(delta)) / 2 * a;
        v = new_vect(r->origin->x + res * r->direction->x, r->origin->y + res * r->direction->y, r->origin->z + res * r->direction->z);
        return (new_hit_point(v, 0.0));
    }
        return (NULL);
}

