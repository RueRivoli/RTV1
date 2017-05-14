/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:23:34 by fgallois          #+#    #+#             */
/*   Updated: 2017/05/12 11:11:22 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

#include <SDL.h>
#include "vector.h"
#include "../framework/SDL2/include/SDL.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct s_ray 
{   
    t_vect      *origin;
    t_vect      *direction;

}               t_ray;

typedef struct s_cam
{
    t_vect      *pos;

}               t_cam;

typedef struct s_screen 
{
    int         nx;
    int         ny;
}               t_screen;

typedef struct s_light 
{
    t_vect          *pos;
    t_vect          *direction;
    float           red;
    float           green;
    float           blue;
}               t_light;

typedef struct s_light_list
{
        t_light     *current;
        t_light     *next;
}               t_light_list;

typedef struct s_win
{
    SDL_Window  *handle;
    SDL_Renderer *rend;
    int         width;
    int         height;
}               t_win;

typedef struct s_obj
{
    int     x;
}           t_obj;

typedef struct s_env
{
    t_win           *win;
    t_screen        *scr;
    t_cam           *cam;
    t_ray            *ray;
    t_obj            *obj;
    SDL_Surface     *background;
}               t_env;


t_env   *init_env(void);
void        render(t_env *env);
#endif
