#include "rtv1.h"

t_cam   *new_cam(t_vect *v1)
{
    t_cam *c;
    if (!(c = (t_cam*)malloc(sizeof(t_cam))))
        return (NULL);
    c->pos = v1;
    return (c);
}

/*t_obj   *add_obj(t_obj *obj, t_vect *vect, int type)
{
    t_obj *tmp;
    t_obj *new;
    if (!obj)
    {
        if (!(obj = (t_obj*)malloc(sizeof(obj))))
            return (NULL);
        obj->vect = vect;
        obj->type = type;
    }
    else 
    {
        tmp = obj;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        if (!(new = (t_obj*)malloc(sizeof(t_obj))))
            return (NULL);
        
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
