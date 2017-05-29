#include "rtv1.h"

t_cone      *new_cone(t_vect *summit, t_vect *axis, float angle)
{
    t_cone      *c;

    if (!(c = (t_cone *)malloc(sizeof(t_cone))))
        return (NULL);
    c->summit = summit;
    c->axis = normed_vector(axis); 
    c->angle = angle;
    return (c);
}

float       alpha_cone(float expr, float n, float dir)
{
    return (n * expr - dir);
}

float       beta_cone(float expr2, float n, float a, float o)
{
    return (n * expr2 + o - a);
}

float       alpha2cone(float expr, float n, float angle)
{
    return (expr * n * tan(angle));
}

float       beta2cone(float expr2, float n, float angle)
{
    return (expr2 * n * tan(angle));
}

t_hit_point         *hit_cone(void *o, t_ray *r)
{
    float a;
    float b;
    float c;
    float expr;
    float expr2;
    float delta;
    t_cone *cone;
    cone = (t_cone *)o;
    t_vect *v;
    float res;

    t_vect *traj;
    
    expr = cone->axis->x * r->direction->x + cone->axis->y * r->direction->y + cone->axis->z * r->direction->z;
    expr2 = (r->origin->x - cone->summit->x) * cone->axis->x + (r->origin->y - cone->summit->y) * cone->axis->y +\
    (r->origin->z - cone->summit->z) * cone->axis->z;
    a =  pow(alpha_cone(expr, cone->axis->x, r->direction->x), 2) + pow(alpha_cone(expr, cone->axis->y, r->direction->y), 2)  +\
    pow(alpha_cone(expr, cone->axis->z, r->direction->z), 2) - pow(alpha2cone(expr, cone->axis->x, cone->angle), 2) - pow(alpha2cone(expr, cone->axis->y, cone->angle), 2) - \
    pow(alpha2cone(expr, cone->axis->z, cone->angle), 2);
    b = term(alpha_cone(expr, cone->axis->x, r->direction->x), beta_cone(expr2, cone->axis->x, r->origin->x, cone->summit->x)) +\
    term(alpha_cone(expr, cone->axis->y, r->direction->y),  beta_cone(expr2, cone->axis->y, r->origin->y, cone->summit->y))  +\
    term(alpha_cone(expr, cone->axis->z, r->direction->z),  beta_cone(expr2, cone->axis->z, r->origin->z, cone->summit->z)) - \
    term(alpha2cone(expr, cone->axis->x, cone->angle), beta2cone(expr2, cone->axis->x, cone->angle)) - term(alpha2cone(expr, cone->axis->y, cone->angle), beta2cone(expr2, cone->axis->y, cone->angle)) - \
    term(alpha2cone(expr, cone->axis->z, cone->angle), beta2cone(expr2, cone->axis->z, cone->angle));
    c = pow(beta_cone(expr2, cone->axis->x, r->origin->x, cone->summit->x), 2) +\
    pow(beta_cone(expr2, cone->axis->y, r->origin->y, cone->summit->y), 2)+\
    pow(beta_cone(expr2, cone->axis->z, r->origin->z, cone->summit->z), 2) - pow(beta2cone(expr2, cone->axis->x, cone->angle), 2) -\
    pow(beta2cone(expr2, cone->axis->y, cone->angle), 2) - pow(beta2cone(expr2, cone->axis->z, cone->angle), 2);
    delta = pow(b, 2) - 4.0 * a * c;
    if (delta >= 0.0)
    {
        res = max((- b - sqrt(delta)) / (2 * a), (- b + sqrt(delta)) / (2 * a));
        traj = multiply_scalar(r->direction, res);
          if (res > 0 /*&& norm(traj) >= r->dist_to_screen*/)
          {
            v = new_vect(r->origin->x + res * r->direction->x, r->origin->y + res * r->direction->y, r->origin->z + res * r->origin->z);
            return (new_hit_point(v, INFINI));
          }
    }
    return (NULL);
}
