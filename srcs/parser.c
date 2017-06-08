#include "rtv1.h"
#include <stdio.h>

int         type_objects(char *str)
{
    if (ft_strcmp(str, "sphere") == 0)
            return (1);
    if (ft_strcmp(str, "plan") == 0)
        return (2);
    if (ft_strcmp(str, "cylinder") == 0)
        return (3);
     if (ft_strcmp(str, "cone") == 0)
        return (4);
    return (0);
}

/*static void         print_obj(t_obj *obj)
{
    t_obj *tmp;
    tmp = obj;
    while (tmp)
    {
        printf("type %d \n", tmp->form);
        tmp = tmp->next;
    }
}*/

void        display_scene(t_env *env)
{
    t_obj *obj;
    t_sphere *sp;
    t_plan *p;
    t_cone *c;
    t_mater *mat;
    t_light *light;
    t_cylinder *cyl;
    obj = env->obj;
    light = env->light;
    t_vect *camera;

    camera = env->cam->pos;
    ft_putstr("Cadre \n\n");
    ft_putstr(env->title);
    ft_putstr("\n");
    ft_putstr("Camera : ");
    ft_putnbr(camera->x);
    ft_putstr(", ");
    ft_putnbr(camera->y);
    ft_putstr(", ");
    ft_putnbr(camera->z);
    ft_putstr("\n");
    ft_putstr("Taille : ");
    ft_putnbr(env->size_x);
    ft_putstr(" ");
    ft_putnbr(env->size_y);
    ft_putstr("\n");
    
    ft_putstr("Light : ");
    while (light)
    {
        ft_putnbr(light->pos->x);
         ft_putstr(", ");
          ft_putnbr(light->pos->y);
           ft_putstr(", ");
        ft_putnbr(light->pos->z);
        ft_putstr("\n");
        light = light->next;
    }
    ft_putstr("\n\n");

    //print_obj(obj);
    ft_putstr("Objects \n\n");
    while (obj)
    {
        mat = obj->mater;
        if (obj->form == 1)
        {   
            sp = (t_sphere*)(obj->type);
            ft_putstr("Sphere \n");
            ft_putstr("Centre : ");
            ft_putnbr(sp->origin->x);
            ft_putstr(", ");
            ft_putnbr(sp->origin->y);
            ft_putstr(", ");
            ft_putnbr(sp->origin->z);
            ft_putstr("\n");
             ft_putstr("Radius : ");
             ft_putnbr(sp->radius);
             ft_putstr("\n");
             ft_putstr("Color : ");
             ft_putnbr(mat->alpha);
             //printf("%f", mat->alpha);
             ft_putstr(", ");
             ft_putnbr(mat->ir);
             ft_putstr(", ");
             ft_putnbr(mat->ig);
             ft_putstr(", ");
             ft_putnbr(mat->ib);
             ft_putstr("\n");

        }
        if (obj->form == 2)
        {  
            p = (t_plan*)(obj->type);
            ft_putstr("Plan \n");
            ft_putstr("Origin : ");
            ft_putnbr(p->origin->x);
            ft_putstr(", ");
            ft_putnbr(p->origin->y);
            ft_putstr(", ");
            ft_putnbr(p->origin->z);
            ft_putstr("\n");
             ft_putstr("Normal : ");
             ft_putnbr(p->normal->x);
            ft_putstr(", ");
            ft_putnbr(p->normal->y);
            ft_putstr(", ");
            ft_putnbr(p->normal->z);
             ft_putstr("\n");
             ft_putstr("Color : ");
             ft_putnbr(mat->alpha);
             //printf("%f", mat->alpha);
             ft_putstr(", ");
             ft_putnbr(mat->ir);
             ft_putstr(", ");
             ft_putnbr(mat->ig);
             ft_putstr(", ");
             ft_putnbr(mat->ib);
             ft_putstr("\n");
        }
         if (obj->form == 3)
        {  
            cyl = (t_cylinder*)(obj->type);
            ft_putstr("Cylinder \n");
            ft_putstr("Origin : ");
            ft_putnbr(cyl->origin->x);
            ft_putstr(", ");
            ft_putnbr(cyl->origin->y);
            ft_putstr(", ");
            ft_putnbr(cyl->origin->z);
            ft_putstr("\n");
             ft_putstr("Normal : ");
             ft_putnbr(cyl->normal->x);
            ft_putstr(", ");
            ft_putnbr(cyl->normal->y);
            ft_putstr(", ");
            ft_putnbr(cyl->normal->z);
             ft_putstr("\n");
             ft_putstr("Radius : ");
             ft_putnbr(cyl->radius);
             ft_putstr("\n");
             ft_putstr("Color : ");
             //printf("%f", mat->alpha);
             ft_putnbr(mat->alpha);
             ft_putstr(", ");
             ft_putnbr(mat->ir);
             ft_putstr(", ");
             ft_putnbr(mat->ig);
             ft_putstr(", ");
             ft_putnbr(mat->ib);
             ft_putstr("\n");
        }
        if (obj->form == 4)
        {  
            c = (t_cone*)(obj->type);
            ft_putstr("Cone \n");
            ft_putstr("Summit : ");
            ft_putnbr(c->summit->x);
            ft_putstr(", ");
            ft_putnbr(c->summit->y);
            ft_putstr(", ");
            ft_putnbr(c->summit->z);
            ft_putstr("\n");
             ft_putstr("Axis : ");
             ft_putnbr(c->axis->x);
            ft_putstr(", ");
            ft_putnbr(c->axis->y);
            ft_putstr(", ");
            ft_putnbr(c->axis->z);
             ft_putstr("\n");
             ft_putstr("Angle : ");
             ft_putnbr(c->angle * 180 / M_PI);
             ft_putstr("\n");
             ft_putstr("Color : ");
             //printf("%f", mat->alpha);
             ft_putnbr(mat->alpha);
             ft_putstr(", ");
             ft_putnbr(mat->ir);
             ft_putstr(", ");
             ft_putnbr(mat->ig);
             ft_putstr(", ");
             ft_putnbr(mat->ib);
             ft_putstr("\n");
        }
        obj = obj->next;
        ft_putchar('\n');
    }
}
t_vect      *read_origin(char *line, int fd, char *str)
{
    t_vect *vect;
    char **tab;

    if (get_next_line(fd, &line) && ft_strstr(line, str))
    {
        tab = ft_strsplit(line, ' ');
        if (tab[1] && tab[2] && tab[3])
            vect = new_vect(ft_atoi(tab[1]), ft_atoi(tab[2]), ft_atoi(tab[3]));
        else
            return (NULL);
    }
    else
        return (NULL);
    free(tab);
    return (vect);
}

float   read_float(char *line, int fd, char *str)
{
    char **tab;
    float res;

    if (get_next_line(fd, &line) && ft_strstr(line, str))
    {
        tab = ft_strsplit(line, ' ');
        if (tab[1])
            res = ft_atoi(tab[1]);
        else
            return (0);
    }
    else
        return (0);
    free(tab);
    return (res);
}

t_mater      *read_mater(char *line, int fd, char *str)
{
    t_mater *mat;
    char **tab;

    if (get_next_line(fd, &line) && ft_strstr(line, str))
    {
        tab = ft_strsplit(line, ' ');
        if (tab[1] && tab[2] && tab[3] && tab[4] && ft_atoi(tab[1]) > -1 && ft_atoi(tab[2]) > -1 && ft_atoi(tab[1]) > -1 && ft_atoi(tab[4]) > -1)
            mat = new_mater(ft_atoi(tab[1]), ft_atoi(tab[2]), ft_atoi(tab[3]), ft_atoi(tab[4]));
        else
            return (NULL);
    }
    else
        return (NULL);
    free(tab);
    return (mat);
}

t_vect      *origin(int to, void *o)
{
    t_vect *v;
    if (to == 1)
    {   
        t_sphere *sp;
        sp = (t_sphere*)o;
        v = sp->origin;
    }
    if (to == 2)
    {   
        t_plan *p;
        p = (t_plan*)o;
        v = p->origin;
    }
    if (to == 3)
    {   
        t_cylinder *cyl;
        cyl = (t_cylinder*)o;
        v = cyl->origin;
    }
    if (to == 4)
    {   
        t_cone *c;
        c = (t_cone*)o;
        v = c->summit;
    }
    return (v);
}

t_vect      *normal(int to, void *o)
{
    t_vect *n;
    n = NULL;
    if (to == 2)
    {   
        t_plan *p;
        p = (t_plan*)o;
        n = p->normal;
    }
    if (to == 3)
    {   
        t_cylinder *cyl;
        cyl = (t_cylinder*)o;
        n = cyl->normal;
    }
    if (to == 4)
    {   
        t_cone *c;
        c = (t_cone*)o;
        n = c->axis;
    }
    return (n);
}

void        modify(void *o, char *line, int fd, int to)
{
    char **tab;
    float theta;
    float mem;
    t_vect *v;
    t_vect *n;
    char *st1;
    char *st2;
    char *st3;
    char *st4;
    char *st5;
    char *st6;
    v = origin(to, o);
    n = normal(to, o);
        while (get_next_line(fd, &line) && ((st1 = ft_strstr(line, "translationX")) || (st2 = ft_strstr(line, "translationY")) || \
        (st3 = ft_strstr(line, "translationZ")) || (st4 = ft_strstr(line, "rotationX")) || (st5 = ft_strstr(line, "rotationY")) || \
        (st6 = ft_strstr(line, "rotationZ"))))
        {
             
            if (ft_strstr(line, "translationX"))
            {
                tab = ft_strsplit(line, ' ');
                if (tab[1])
                    v->x += ft_atoi(tab[1]);
             }
            if (ft_strstr(line, "translationY"))
            {
                ft_putstr("FF");
                tab = ft_strsplit(line, ' ');
                if (tab[1])
                    v->y += ft_atoi(tab[1]);
            }
            if (ft_strstr(line, "translationZ"))
            {
                tab = ft_strsplit(line, ' ');
                if (tab[1])
                    v->z += ft_atoi(tab[1]);
            }
            if (ft_strstr(line, "rotationX") && to != 1)
            {
               ft_putstr("FF");
                tab = ft_strsplit(line, ' ');
                if (tab[1])
                {
                    theta = ft_atoi(tab[1]) * M_PI / 180;
                    mem = n->y;
                    n->y = cos(theta) * n->y + sin(theta) * n->z;
                    n->z = -sin(theta) * mem + cos(theta) * n->z;
                    n = normed_vect(n);
                    //printf("%.2f %.2f", p->normal->y, p->normal->z);
                }
            }
            if (ft_strstr(line, "rotationY") && to != 1)
            {
                tab = ft_strsplit(line, ' ');
                if (tab[1])
                {
                    theta = ft_atoi(tab[1]) * M_PI / 180;
                    mem = n->x;
                    n->x = cos(theta) * n->x + sin(theta) * n->z;
                    n->z = -sin(theta) * mem + cos(theta) * n->z;
                    n = normed_vect(n);
                }
                
            }
            if (ft_strstr(line, "rotationZ") && to != 1)
            {
                tab = ft_strsplit(line, ' ');
                if (tab[1])
                {
                    theta = ft_atoi(tab[1]) * M_PI / 180;
                    mem = n->x;
                    n->x = cos(theta) * n->x + sin(theta) * n->y;
                    n->y = -sin(theta) * mem + cos(theta) * n->y;
                    n = normed_vect(n);
                }
            }
        }
}

int         register_sphere(char *line, t_env *env, int fd)
{
    t_vect *vect;
    float rad;
    t_mater *mat;
    t_sphere *sp;
    
    mat = NULL;
   
    if (!(vect = read_origin(line, fd, "origin")))
        return (0);
    if (!(rad = read_float(line, fd, "radius")))
        return (0);
    if (!(mat = read_mater(line, fd, "color")))
        return (0);
    sp = new_sphere(vect, rad);
    modify((void*)sp, line, fd, 1);
    env->obj = add_obj(env->obj, 1, mat, (void*)sp);
    return (1);
}

int         register_plan(char *line, t_env *env, int fd)
{
    t_vect *vect;
    t_vect *norm;
    t_mater *mat;
    t_plan *p;

    if (!(vect = read_origin(line, fd, "origin")))
        return (0);
    if (!(norm = read_origin(line, fd, "normal")))
        return (0);
    if (!(mat = read_mater(line, fd, "color")))
        return (0);
     p = new_plan(vect, normed_vect(norm));
    modify((void*)p, line, fd, 2);
     env->obj = add_obj(env->obj, 2, mat, (void*)p);
    return (1);
}

int         register_cylinder(char *line, t_env *env, int fd)
{
    t_vect *vect;
    t_vect *norm;
    float rad;
    t_mater *mat;
    t_cylinder *cyl;
   if (!(vect = read_origin(line, fd, "origin")))
        return (0);
     if (!(norm = read_origin(line, fd, "normal")))
        return (0);
    if (!(rad = read_float(line, fd, "radius")))
        return (0);
    if (!(mat = read_mater(line, fd, "color")))
        return (0);
    cyl = new_cylinder(vect, norm, rad);
    modify((void*)cyl, line, fd, 3);
        env->obj = add_obj(env->obj, 3, mat, (void*)cyl);
    return (1);
}

int         register_cone(char *line, t_env *env, int fd)
{
    t_vect *vect;
    t_vect *axis;
     float angle;
    t_mater *mat;
    t_cone *cone;
    if (!(vect = read_origin(line, fd, "summit")))
        return (0);
     if (!(axis = read_origin(line, fd, "axis")))
        return (0);
    if (!(angle = read_float(line, fd, "angle")))
        return (0);
    if (!(mat = read_mater(line, fd, "color")))
        return (0);
    cone = new_cone(vect, axis, angle);
    modify((void*)cone, line, fd, 4);
    cone->angle = cone->angle * M_PI / 180;
    env->obj = add_obj(env->obj, 4, mat, (void*)cone);
    return (1);
}

int         registering(int to, char *line, t_env *env, int fd)
{
    if (to == 1)
        return (register_sphere(line, env, fd));
    if (to == 2)
        return (register_plan(line, env, fd));
    if (to == 3)
        return (register_cylinder(line, env, fd));
    if (to == 4)
        return (register_cone(line, env, fd));
    return (0);
}

int         read_objects(int fd, char *line, t_env *env)
{
    int to;
    char *str;
    int ret;
    ret = 1;
    to = 0;
    while (get_next_line(fd, &line) && ret)
    {
        if (ft_strstr(line, "name") && (str = ft_strsplit(line, ' ')[1]))
        {
            to = type_objects(str);
            if (to < 1 || to > 4)
                return (0);
            ret = registering(to, line, env, fd);
        }
    }
    return (ret);
}

int        read_scene(int fd, char *line, t_env *env)
{
    char *str;
    char **tab;
    t_vect *v;
    t_vect *trans;
    str = NULL;
    tab = NULL;
     v = NULL;
     int ret;
     ret = 0;
    if (get_next_line(fd, &line) && ft_strstr(line, "name"))
    {
        if ((str = ft_strsplit(line, ' ')[1]))
        {
            env->title = str;
            ret++;
        }
    }
    if (get_next_line(fd, &line) && ft_strstr(line, "camera"))
    {
        tab = ft_strsplit(line, ' ');
       
        if (tab[2] != NULL && tab[3]!= NULL && tab[4] != NULL)
        {
            v = new_vect(ft_atoi(tab[2]),ft_atoi(tab[3]), ft_atoi(tab[4]));
            ret++;
        }
        trans = new_vect(0.0, 0.0, 0.0);
        env->cam = new_cam(v, trans, 0.0, 0.0);
    }
    if (get_next_line(fd, &line) && ft_strstr(line, "render"))
    {
        tab = ft_strsplit(line, ' ');
        if (tab[2] != NULL && tab[3] != NULL)
          {
               env->size_x = ft_atoi(tab[2]);
                env->size_y = ft_atoi(tab[3]);
                env->win->height = ft_atoi(tab[3]);
                env->win->width = ft_atoi(tab[2]);
                ret++;
          }
    }
    while (get_next_line(fd, &line) && ft_strstr(line, "spot"))
    {
        tab = ft_strsplit(line, ' ');
        if (tab[1] && tab[2] && tab[3])
          {
               v = new_vect(ft_atoi(tab[1]), ft_atoi(tab[2]), ft_atoi(tab[3]));
               env->light = add_light(env->light, v);
                ret++;
          }
    }
    return (ret);
}

int        lecture(int fd, t_env *env)
{
    char *line;
    int index;
    index = 0;
    while (get_next_line(fd, &line))
    {
        if (ft_strstr(line, "# Scene")!= NULL)
        {
                index++;
                get_next_line(fd, &line);
                
               if (index != 1 || read_scene(fd, line,env) < 3)
                {
                    error_param();
                    return (0);
                }
        }
        
        if (ft_strstr(line, "# Objects") != NULL)
        {
                index++;
                get_next_line(fd, &line);
                              
               if (index != 2 || read_objects(fd, line,env) == 0)
                {
                    error_param();
                    return (0);

                }
                
   
        }
    }
    if (index < 2)
    {
        error_param();
        return (0);
    }
    return (1);
}
