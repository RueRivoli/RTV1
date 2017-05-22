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
        obj->mater = mater;
        obj->next = NULL;
    }
    else 
    {
        tmp = obj;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        new = (t_obj*)malloc(sizeof(t_obj));
        new->is_hit = get_obj_collider(obj_type);
        new->type = type;
        new->mater = mater;
        new->next = NULL;
        tmp->next = new;
    }
    return (obj);
}
/*t_obj       add_obj(t_obj **obj, int obj_type, t_vect *mater, void *type)
{
    t_obj *tmp;
    if (!*obj)
    {
        if (!(*obj = (t_obj*)malloc(sizeof(t_obj))))
            return (NULL);
        (*obj)->is_hit = get_obj_collider(obj_type);
        (*obj)->type = type;
        (*obj)->mater = mater;
        (*obj)->next = NULL;
    }
    else 
    {
        tmp = *obj;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp = malloc(sizeof(t_geo));
        tmp->type = type;
        tmp->mater = mater;
        tmp->next = NULL;
    }

}*/

t_hit_point     *new_hit_point(t_vect *vect, float dist_to_cam)
{
    t_hit_point *ht;
    if (!(ht = (t_hit_point*)malloc(sizeof(t_hit_point))))
        return (NULL);
    ht->vect = vect;
    ht->distance_to_cam = dist_to_cam; 
    return (ht);
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
