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

t_plan  *new_plan(t_vect *origin, t_vect *normal)
{
    t_plan      *plan;

    if (!(plan = (t_plan *)malloc(sizeof(t_plan))))
        return (NULL);
    plan->origin = origin;
    plan->normal = normal;
    return (plan);
}

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

int         belong_to_plan(t_plan *p, t_vect *v)
{
    t_vect  *v1;
    v1 = minus_vect(v, p->origin);
    if (scalar_product(v1, p->normal) == 0.0)
        return (1);
    return (0);
}

int         belong_to_cylinder(t_cylinder *c, t_vect *v)
{
    t_vect  *v1;

    v1 = minus_vect(v, c->origin);
    if (distance(v, add_vect(c->origin, multiply_scalar(normed_vector(c->normal), scalar_product(v, normed_vector(c->normal))))) <= c->radius)
        return (1);
    return (0);
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

float       sec_deg_eq(float n, float dir)
{
    return (pow(n - 1.0, 2) * pow(dir, 2));
}

float       sec_deg_eq2(float expr, float n, float dir)
{
    return (pow(n * expr - dir, 2));
}
float       fst_deg_eq(float n, float dir, float a, float o)
{
    return (2 * n * dir * (a - o) * (n - 1.0) + 2 * a * dir * pow(n - 1, 2));
}

float       fst_deg_eq2(float n, float dir, float a, float o, float expr, float expr2)
{
    return (2 * (n * expr - dir) * ((o - a) + expr2 * n));
}
float       zer_deg_eq(float n, float a, float o)
{
    return (pow(a - o, 2) * pow(n, 2) + 2 * n * (a - o) * (n - 1.0) * a + pow(a, 2) * pow(n - 1.0, 2));
}

float       zer_deg_eq2(float n, float expr2, float o, float a)
{
    return (pow( (o - a) + expr2 * n, 2));
}

int         hit_cylinder3(t_cylinder *cyl, t_ray *r)
{
    float a;
    float b;
    float c;
    float expr;
    float expr2;
    float delta;

    expr = cyl->normal->x * r->direction->x + cyl->normal->y * r->direction->y + cyl->normal->z * r->direction->z;
    //printf("expr : %f\n", expr);
    expr2 = (r->origin->x - cyl->origin->x) * cyl->normal->x + (r->origin->y - cyl->origin->y) * cyl->normal->y +\
    (r->origin->z - cyl->origin->z) * cyl->normal->z;
    //printf("expr2 : %f\n",expr2);
    a =  sec_deg_eq2(expr, cyl->normal->x, r->direction->x) + sec_deg_eq2(expr, cyl->normal->y, r->direction->y) +\
    sec_deg_eq2(expr, cyl->normal->z, r->direction->z);
    //printf("a : %f\n",a);
    b = fst_deg_eq2(cyl->normal->x, r->direction->x, r->origin->x, cyl->origin->x, expr, expr2) +\
    fst_deg_eq2(cyl->normal->y, r->direction->y, r->origin->y, cyl->origin->y, expr, expr2) +\
    fst_deg_eq2(cyl->normal->z, r->direction->z, r->origin->z, cyl->origin->z, expr, expr2);
    //printf("b : %f\n",b);
    c = zer_deg_eq2(cyl->normal->x, expr2, cyl->origin->x, r->origin->x) +\
    zer_deg_eq2(cyl->normal->y, expr2, cyl->origin->y, r->origin->y) +\
    zer_deg_eq2(cyl->normal->z, expr2, cyl->origin->z, r->origin->z) - pow(cyl->radius, 2);
    //printf("c : %f\n",c);
    delta = pow(b, 2) - 4 * a * c;
        //printf("%f\n", delta);
    if (delta >= 0)
        return (1);
    return (0);
}

int         hit_cylinder2(t_cylinder *cyl, t_ray *r)
{
    float a;
    float b;
    float c;
    float delta;
    a =  sec_deg_eq(cyl->normal->x, r->direction->x) + sec_deg_eq(cyl->normal->y, r->direction->y) + sec_deg_eq(cyl->normal->z, r->direction->z);
    b = fst_deg_eq(cyl->normal->x, r->direction->x, r->origin->x, cyl->origin->x) + fst_deg_eq(cyl->normal->y, \
    r->direction->y, r->origin->y, cyl->origin->y) + fst_deg_eq(cyl->normal->z, \
    r->direction->z, r->origin->z, cyl->origin->z);
    c = zer_deg_eq(cyl->normal->x, r->origin->x, cyl->origin->x) + zer_deg_eq(cyl->normal->y, \
    r->origin->y, cyl->origin->y) + zer_deg_eq(cyl->normal->z, r->origin->z, cyl->origin->z) - pow(cyl->radius, 2);
    delta = pow(b, 2) - 4 * a * c;
    if (delta >= 0)
        return (1);
    return (0);
}
/*int         hit_cylinder(t_cylinder *cyl, t_ray *r)
{
    t_vect *l;
    t_vect *w;
    t_vect *d;
    t_vect *E;
    t_vect *F;
    float w2;
    float a;
    float D;
    float R;
    float t;
    float s;
    l = minus_vect(r->origin, cyl->origin);
    w = product_vectorial(normed_vect(r->direction), normed_vect(cyl->normal));
    w2 = scalar_product(w, w);
    if (w2 == 0)
    {
        a = scalar_product(l, normed_vector(cyl->normal));
        d = minus_vect(l, multiply_scalar(a, normed_vector(cyl->normal)));
        D = scalar_product(d, d);
        if (D > power(cyl->radius, 2))
            return (0);
        return (1);
    }
    else 
    {
        R = scalar_product(l, normed_vector(w));
        if (R > cyl->radius)
            return (0);
        else 
        {
            E = product_vectorial(l, normed_vect(v));
            t = -1 * scalar_product(E, normed_vector(w));
            F = product_vectorial(w, cyl->normal);
            s = sqrt(power(cyl->radius, 2) - power(R, 2)) / scalar_product(normed_vector(r->direction), \
            normed_vect(F));
            intersection = cyl->origin + (t +- s).u;
        }
    }

}*/

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

int         hit_sphere(t_sphere *sp, t_ray *r)
{
    float delta;
    float a;
    delta = 2 * (r->origin->x * r->direction->x + r->origin->y * r->direction->y + r->origin->z * r->direction->z - (r->direction->x * sp->origin->x +\
    r->direction->y * sp->origin->y + r->direction->z * sp->origin->z));
    delta = pow(delta, 2);
    a = pow(r->direction->x, 2) + pow(r->direction->y, 2) + pow(r->direction->z, 2);
    
    a *= pow(r->origin->x, 2) + pow(r->origin->y, 2) + pow(r->origin->z, 2) + pow(sp->origin->x, 2) + pow(sp->origin->y, 2) + pow(sp->origin->z, 2) - 2 * (sp->origin->x * r->origin->x + sp->origin->y  * r->origin->y + sp->origin->z * r->origin->z) - pow(sp->radius, 2);
    delta = delta - 4 * a;
     
    if (delta >= 0)
    {
        return (1);
    } 
    return (0);
}
