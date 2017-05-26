#include "rtv1.h"

t_cam   *new_cam(t_vect *v1)
{
    t_cam *c;
    if (!(c = (t_cam*)malloc(sizeof(t_cam))))
        return (NULL);
    c->pos = v1;
    return (c);
}

t_mater   *new_mater(float f, int r, int g, int b)
{
    t_mater *mat;
    if (!(mat = (t_mater*)malloc(sizeof(t_mater))))
        return (NULL);
    mat->alpha = f;
    mat->ir = r;
    mat->ig = g;
    mat->ib = b;
    return (mat);
}

t_vect      *center_average(t_env *env)
{   
    t_obj *obj;
    obj = env->obj;
    float x;
    float y;
    float z;
    int ct;
    ct = 0;
    x = 0;
    y = 0;
    z = 0;
    while (obj)
    {
        ct++;
        if (obj->form == 1)
        {
            t_sphere *sp;
            sp = (t_sphere*)obj->type;
            x += sp->origin->x;
            y += sp->origin->y;
            z += sp->origin->z;
        }
        else if (obj->form == 2)
        {
            t_plan *p;
            p = (t_plan*)obj->type;
            x += p->origin->x;
            y += p->origin->y;
            z += p->origin->z;
        }
        else if (obj->form == 3)
        {
            t_cylinder *cyl;
            cyl = (t_cylinder*)obj->type;
            x += cyl->origin->x;
            y += cyl->origin->y;
            z += cyl->origin->z;
        }
        else if (obj->form == 4)
        {
            t_cone *c;
            c = (t_cone*)obj->type;
            x += c->summit->x;
            y += c->summit->y;
            z += c->summit->z;
        }
        obj = obj->next;
    }
    return (new_vect(x/ct, y/ct, z/ct));
}

t_vect      *vectv(t_vect *n)
{
    float x;
    float y;
    float z;
    x = 1.0;
    y = -n->x /n->y;
    z = 0.0;

    return (normed_vector(new_vect(x, y, z)));
}

t_vect      *vectw(t_vect *n)
{
    float x;
    float y;
    float z;
    
    y = -0.5 * n->z / (n->y + pow(n->x, 2)/ n->y);
    x = (n->x / n->z) * y;
    z = 0.5;
    return (normed_vector(new_vect(x, y, z)));
}

void    set_virtual_screen(t_env *env)
{
    t_vect *v;
    t_vect *n;

    v = minus_vect(center_average(env), env->cam->pos);
    n = normed_vector(v);
    v = multiply_scalar(n, 100);
    v = add_vect(env->cam->pos, v);
    if (!(env->screen = (t_screen*)malloc(sizeof(t_screen))))
        return ;
    env->screen->center = v;
    env->screen->v = vectv(n);
    env->screen->w = vectw(n);
}

t_hit_point         *(*get_obj_collider(int id))(void *o, t_ray *r)
{
    if (id == 1)
        return (*hit_sphere);
    if (id == 2)
        return (*hit_plan);
    if (id == 3)
        return (*hit_cylinder);
    if (id == 4)
        return (*hit_cone);
    return (NULL);
}


t_light       *add_light(t_light *light, t_vect *pos)
{
    t_light *tmp;
    t_light *new;
    if (!light)
    {
        if (!(light = (t_light*)malloc(sizeof(t_light))))
            return (NULL);
        light->pos = pos;
        light->next = NULL;
    }
    else 
    {
        tmp = light;
        while (tmp->next)
            tmp = tmp->next;
        new = (t_light*)malloc(sizeof(t_light));
        new->pos = pos;
        new->next = NULL;
        tmp->next = new;
    }
    return (light);
}

t_obj       *add_obj(t_obj *obj, int obj_type, t_mater *mater, void *type)
{
    t_obj *tmp;
    t_obj  *new;
    if (!obj)
    {
        if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
            return (NULL);
        obj->is_hit = get_obj_collider(obj_type);
        obj->type = type;
        obj->form = obj_type;
        obj->mater = mater;
        obj->next = NULL;
    }
    else 
    {
        tmp = obj;
        while (tmp->next)
            tmp = tmp->next;
        new = (t_obj*)malloc(sizeof(t_obj));
        new->is_hit = get_obj_collider(obj_type);
        new->type = type;
        new->mater = mater;
        new->form = obj_type;
        new->next = NULL;
        tmp->next = new;
    }
    return (obj);
}

t_hit_point     *new_hit_point(t_vect *vect, float dist_to_cam)
{
    t_hit_point *ht;
    if (!(ht = (t_hit_point*)malloc(sizeof(t_hit_point))))
        return (NULL);
    ht->vect = vect;
    ht->distance_to_cam = dist_to_cam; 
    return (ht);
}

float       distance_with_cam(t_env *env, t_hit_point *hp)
{
    t_vect *pos;
    t_vect *diff;
    pos = env->cam->pos;
    if (!hp)
        return (INFINI); 
    diff = minus_vect(pos, hp->vect);
    return (sqrt(pow(diff->x, 2) + pow(diff->y, 2) + pow(diff->z, 2)));
}

t_ray   *new_ray(t_vect *orig, t_vect *dir)
{
    t_ray *r;
    if (!(r = (t_ray*)malloc(sizeof(t_ray))))
        return (NULL);
    r->origin = orig;
    r->direction = dir;
    r->hit_point = NULL;
    return (r);
}

float       term(float alpha, float beta)
{
    return (2 * alpha * beta);
}
