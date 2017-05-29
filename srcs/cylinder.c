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
    t_vect *traj;
    float res;
    t_vect *v;
    float oh;
    float oa;
    t_cylinder *cyl;
    t_vect *w;

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
    //ft_putnbr(colin(r->direction, cyl->normal));
    //ft_putnbr(delta);

     if (colin(r->direction, cyl->normal) == 1)
    {
    
        oh = scalar_product(minus_vect(r->origin, cyl->origin), cyl->normal);
        oa = norm(minus_vect(r->origin, cyl->origin));
        
        v = new_vect(INFINI, INFINI, INFINI);
        
        if (sqrt(pow(oa, 2) - pow(oh, 2)) <= cyl->radius)
        {
            w = new_vect(INFINI - 1, INFINI - 1, INFINI - 1);
             return (new_hit_point(w, -1.0));
        }
    }
     else if (delta >= 0.0)
    {
            
            res = max((- b - sqrt(delta)) / (2 * a), (- b + sqrt(delta)) / (2 * a));
            //ft_putnbr(res);
            //ft_putchar('\n');
            //ft_putnbr(res);
            //ft_putchar('\n');
            traj = multiply_scalar(r->direction, res);
            //ft_putstr("Trajet : ");
            //ft_putnbr(traj->x);
            //ft_putnbr(100 * r->direction->x);
            //ft_putchar('\n');
            //ft_putnbr(100 * r->direction->y);
            //ft_putchar('\n');
            //ft_putnbr(100 * r->direction->z);
            //ft_putchar('\n');
            //ft_putchar('\n');
            //ft_putnbr(r->dist_to_screen);
            ///ft_putchar('\n');
            //dist_sc = new_vect(env->x - r->origin->x, env->y - r->origin->y, - r->origin->z));
            if (res > 0 && norm(traj) >= r->dist_to_screen)
            {
                v = new_vect(r->origin->x + res * r->direction->x, r->origin->y + res * r->direction->y, r->origin->z + res * r->direction->z);
                return (new_hit_point(v, INFINI));
            }
            else 
                return (NULL);
    }
    
    
        return (NULL);
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

t_hit_point         *hit_cylinder3(void *o, t_ray *r)
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

    cyl = (t_cylinder *)o;
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
    {
        res = (- b - delta )/ 2 * a;
        v = new_vect(r->origin->x + res * r->direction->x, r->origin->y + res * r->direction->y, r->origin->z + res * r->direction->z);
        return (new_hit_point(v, INFINI));
    }
    return (NULL);
}
