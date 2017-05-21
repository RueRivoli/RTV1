#include "rtv1.h"

/*static int     ft_strlent(char **tab)
{
    int i;
    i = 0;
    while (tab[i])
        i++;
    return (i);
}*/

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
               if (index != 1 || read_scene(fd, line,env) != 3)
                {
                    error_param();
                    return (0);
                }
        }
        if ((st1 = ft_strstr(line, "Objects")) != NULL)
        {
                index++;
               if (index != 2 || read_objects(fd, line,env) != 3)
                {
                    error_param();
                    return (0);
                }
        }

    }
    return (1);
}

