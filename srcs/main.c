/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:54:51 by fgallois          #+#    #+#             */
/*   Updated: 2017/05/15 14:09:49 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/rtv1.h"
# include <SDL2/SDL.h>
# include <stdlib.h>
#include <stdio.h>
# include <math.h>

int        event(t_env *env)
{
    SDL_Event   evenements;

    SDL_WaitEvent(&evenements);
    if (evenements.type == SDL_KEYDOWN && evenements.key.keysym.sym == SDLK_ESCAPE)
                return (0);
	else if (evenements.type == SDL_QUIT)
                return (0);
    else if (evenements.type == SDL_WINDOWEVENT)
    {
        if(evenements.window.event == SDL_WINDOWEVENT_RESIZED)
                printf("Fenêtre redimensionnée\n"); /* Fenêtre redimensionnée */
        if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
                return (0);
    }
	else if (evenements.type == SDL_WINDOWEVENT_SIZE_CHANGED)
			SDL_RenderClear(env->win->rend);
        return (1);
}

void        quit_SDL(t_env *env)
{
    SDL_DestroyRenderer(env->win->rend);
    SDL_DestroyWindow(env->win->handle);
    SDL_Quit();
}

void        trace(t_env *env, t_cone *cone)
{
    int x;
    int y;
    t_vect *v;
    t_ray *r;

        x = 0;
        while (x < 900)
        {
            y = 0;
            while (y < 700)
            {
                v = new_vect(x, y, 0.0);
                r = new_ray(env->cam->pos, normed_vector(minus_vect(v, env->cam->pos)));  
                /*if (hit_sphere(sp, r) == 1)
                        SDL_RenderDrawPoint(env->win->rend, x, y);*/
                /*if (hit_plan(p, r) == 1)
                        SDL_RenderDrawPoint(env->win->rend, x, y);*/
                /*if (x == 100 && y == 100)
                {*/
                         if (hit_cone(cone, r))
                        SDL_RenderDrawPoint(env->win->rend, x, y);
                    
                /*}*/
                y++;
            }
            x++;
        }
        //SDL_RenderPresent(env->win->rend);
        //SDL_UpdateWindowSurface(env->win->handle);
}

int main(int argc, char **argv)
{
    t_env *env;
    int fd;
    (void)env;
    
    if (!(env = init_env()))
        return (0);
      
    if (argc != 2)
    {
        error_param();
        return (0);
    }
    fd = open(argv[1], O_RDONLY);
    if (lecture(fd, env) != 0)
        display_scene(env);
    /*t_vect *v1;
    t_vect *norm;
    t_cone *c;

    if (!(v1 = new_vect(450.0, 350.0, 200.0)))
        return (0);
   
    if (!(norm = new_vect(10.0, 10.0, 10.0)))
        return (0);
    if (!(c = new_cone(v1, norm, 10.0)))
        return (0);
    
     while(!env->boucle)
    {
        SDL_SetRenderDrawColor(env->win->rend, 160, 160, 160, 0);
        SDL_RenderClear(env->win->rend);
    //On met le fond en couleur
       
    //Couleur de dessin :
        //SDL_SetRenderDrawColor(env->win->rend, 50, 50, 50, 255);

        //SDL_GetWindowSize(env->win->handle, size_x, size_y);
       //SDL_GetWindowPosition(env->win->handle, pos_x, pos_y);
       
       SDL_SetRenderDrawColor(env->win->rend, 255, 0, 0, 0);
        trace(env, c);
        SDL_RenderPresent(env->win->rend);
        //SDL_UpdateWindowSurface(env->win->handle);

        if (event(env) == 0)
            env->boucle = 1;
    }
    
    
    quit_SDL(env);*/
    return (0); 
}
