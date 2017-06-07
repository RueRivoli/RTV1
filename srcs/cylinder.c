#include "rtv1.h"

t_cylinder  *new_cylinder(t_vect *origin, t_vect *normal, float radius)
{
    t_cylinder      *cyl;

    if (!(cyl = (t_cylinder *)malloc(sizeof(t_cylinder))))
        return (NULL);
    cyl->origin = origin;
    cyl->normal = normed_vect(normal); 
    cyl->radius = radius;
    return (cyl);
}

int         belong_to_cylinder(t_cylinder *c, t_vect *v)
{
    t_vect  *v1;
    t_vect *norm;
    t_vect *p;

    v1 = minus_vect(v, c->origin);
    norm = normed_vect(c->normal);
    p = multiply_scalar(norm , scalar_product(v, norm));
    if (distance(v, add_vect(c->origin, p)) <= c->radius)
    {
        free(p);
        free(norm);
        return (1);
    }
    free(p);
    free(norm);
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

t_vect              *normal_cylinder(t_cylinder *cyl, t_vect *p)
{
    t_vect *h;
    t_vect *v;
    t_vect *n;
    t_vect *min;
    t_vect *ad;
    n = normed_vect(cyl->normal);
    p = minus_vect(p, cyl->origin);
    h = multiply_scalar(n , scalar_product(p, n));
    ad = add_vect(cyl->origin, h);
    min = minus_vect(p, ad);
    v = normed_vect(min);
    free(p);
    free(h);
    free(ad);
    free(min);
    return (v);
}

t_hit_point         *hit_cylinder(void *o, t_ray *r)
{
    float a;
    float b;
    float c;
    float expr;
    float expr2;
    float delta;
    //t_vect *traj;
    float res;
    t_vect *v;
    t_vect *y;
    t_vect *t;
    float oh;
    float oa;
    t_cylinder *cyl;
    t_hit_point *hp;
    t_vect *w;
    t_vect *norm_cyl;
    t_vect *v0;

    //t_vect      *dist_sc;
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
     if (colin(r->direction, cyl->normal) == 1)
    {
        w = minus_vect(r->origin, cyl->origin);
        oh = scalar_product(w, cyl->normal);
        oa = norm(w);
        
        v = new_vect(INFINI, INFINI, INFINI);
        
        if (sqrt(pow(oa, 2) - pow(oh, 2)) <= cyl->radius)
        {
            y = new_vect(INFINI - 1, INFINI - 1, INFINI - 1);
            v0 = new_vect(0,0,0);
            hp = new_hit_point(y, -1.0, v0, 3);
            free(v0);
            free(y);
            free(v);
            free(w);
             return (hp);
        }
    }
     else if (delta >= 0.0)
    {
            //res = max((- b - sqrt(delta)) / (2 * a), (- b + sqrt(delta)) / (2 * a));
            
            res = min_positiv_s((- b - sqrt(delta)) / (2 * a), (- b + sqrt(delta)) / (2 * a), 0);
            //traj = multiply_scalar(r->direction, res);
            if (res > 0 /*&& norm(traj) >= r->dist_to_screen*/)
            {
                t = new_vect(r->origin->x + res * r->direction->x, r->origin->y + res * r->direction->y, r->origin->z + res * r->direction->z);
                norm_cyl = normal_cylinder(cyl, t);
                hp = new_hit_point(t, INFINI, norm_cyl, 3);
                free(t);
                free(norm_cyl);
                return (hp);
            }
            else 
                return (NULL);
    }
    
    
        return (NULL);
}

