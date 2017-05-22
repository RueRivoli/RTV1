#include "rtv1.h"

/*static int     ft_strlent(char **tab)
{
    int i;
    i = 0;
    while (tab[i])
        i++;
    return (i);
}*/

int         type_objects(char *str)
{
    if (ft_strcmp(str, "sphere"))
        return (1);
    if (ft_strcmp(str, "plan"))
        return (2);
    if (ft_strcmp(str, "cylinder"))
        return (3);
     if (ft_strcmp(str, "cone"))
        return (4);
    return (0);
}

int         register_sphere(char *line, t_env *env, int fd)
{
    char **tab;
    t_vect *vect;
    t_mater *mat;
    t_sphere *sp;
    float rad;
    int ret;
    ret = 0;
    if (get_next_line(fd, &line) && ft_strstr(line, "vect"))
    {
        tab = ft_strsplit(line, ' ');
        if (tab[1] && tab[2] && tab[3])
        {
            vect = new_vect(ft_atoi(tab[1]), ft_atoi(tab[2]), ft_atoi(tab[3]));
            to = type_objects(str);
            ret++;
        }
    }
    if (get_next_line(fd, &line) && ft_strstr(line, "radius"))
    {
        tab = ft_strsplit(line, ' ');
       
        if (tab[1] && tab[2]== NULL)
        {
            rad = ft_atoi(tab[1]);
            ret++;
        }
    }
    if (get_next_line(fd, &line) && ft_strstr(line, "color"))
    {
        tab = ft_strsplit(line, ' ');
       
        if (tab[1] && tab[2] && tab[3] && tab[4])
        {
            mat = new_mater(ft_atoi(tab[1]), ft_atoi(tab[2]), ft_atoi(tab[3]), ft_atoi(tab[4]));
            ret++;
        }
        sp = new_sphere(vect, rad);
        env->obj = add_obj(env->obj, 1, mat, (void*)sp);
    }
    return (ret);
}


int         register(int to, char *line, t_env *env)
{
    if (to == 1)
        return (register_sphere(line, env));
    return (0);
}

int         read_objects(int fd, char *line, t_env *env)
{
    int to;
    char *str;
    if (get_next_line(fd, &line) && ft_strstr(line, "name"))
    {
        if ((str = ft_strsplit(line, ' ')[1]))
        {
            to = type_objects(str);
            if (to == 0)
                return (0);
            ret++;
        }
        return (register(to, line, env));
    }
    return (0);
}

int        read_scene(int fd, char *line, t_env *env)
{
    char *str;
    char **tab;
    t_vect *v;
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
        //ft_putstr(line);
        tab = ft_strsplit(line, ' ');
       
        if (tab[2] != NULL && tab[3]!= NULL && tab[4] != NULL)
        {
            v = new_vect(ft_atoi(tab[2]),ft_atoi(tab[3]), ft_atoi(tab[4]));
            ret++;
        }
       env->cam = new_cam(v);
    }
    if (get_next_line(fd, &line) && ft_strstr(line, "render"))
    {
        //ft_putstr(line);
        tab = ft_strsplit(line, ' ');
        if (tab[2] != NULL && tab[3] != NULL)
          {
               env->size_x = ft_atoi(tab[2]);
                env->size_y = ft_atoi(tab[3]);
                ret++;
          }
    }
    return (ret);
}

int        lecture(int fd, t_env *env)
{
    char *line;
    char *st1;
    int index;
    index = 0;
    while (get_next_line(fd, &line))
    {
        //ft_putstr(line);
        if ((st1 = ft_strstr(line, "Scene")) != NULL)
        {
                index++;
                get_next_line(fd, &line);
               if (index != 1 || read_scene(fd, line,env) != 3)
                {
                    error_param();
                    return (0);
                }
        }
        if ((st1 = ft_strstr(line, "Objects")) != NULL)
        {
                index++;
                get_next_line(fd, &line);
               if (index != 2 || read_objects(fd, line,env) != 3)
                {
                    error_param();
                    return (0);
                }
        }

    }
    return (1);
}
