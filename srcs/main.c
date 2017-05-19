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
        else if (evenements.type == SDL_WINDOWEVENT){
            if(evenements.window.event == SDL_WINDOWEVENT_RESIZED) {
                printf("Fenêtre redimensionnée\n"); /* Fenêtre redimensionnée */
            }
            if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
                return (0);
        }
		else if (evenements.type == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				SDL_RenderClear(env->win->rend);
			}
        return (1);
}

void        quit_SDL(t_env *env)
{
    SDL_DestroyRenderer(env->win->rend);
    SDL_DestroyWindow(env->win->handle);
    SDL_Quit();
}

void        trace(t_env *env)
{
    int x;
    int y;
    t_vect *v;
    t_ray *r;
    //t_plan *p;
    t_vect *v1;
    t_vect *norm;
    t_cylinder *cyl;
    //SDL_SetRenderDrawColor(env->win->rend, 255, 0, 0, 0);
    if (!(v1 = new_vect(600.0, 450.0, 100.0)))
        return;
    if (!(norm = new_vect(0.0, 10.0, 0.0)))
        return;
    if (!(cyl = new_cylinder(v1, norm, 195.0)))
        return;
    /*if (!(sp = new_sphere(v1, 200.0)))
        return;*/
   /*if (!(p = new_plan(v1, norm)))
        return;*/
        x = 0;
        while (x < 1200)
        {
            y = 0;
            while (y < 900)
            {
                v = new_vect(x, y, 0.0);
                r = new_ray(env->cam->pos, normed_vector(minus_vect(v, env->cam->pos)));  
                /*if (hit_sphere(sp, r) == 1)
                        SDL_RenderDrawPoint(env->win->rend, x, y);*/
                /*if (hit_plan(p, r) == 1)
                        SDL_RenderDrawPoint(env->win->rend, x, y);*/
                if (hit_cylinder3(cyl, r) == 1)
                    SDL_RenderDrawPoint(env->win->rend, x, y);
                y++;
            }
            x++;
        }
        //SDL_RenderPresent(env->win->rend);
        //SDL_UpdateWindowSurface(env->win->handle);
}

int main(GLvoid)
{
    t_env *env;
    
    if (!(env = init_env()))
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
       
       //SDL_SetRenderDrawColor(env->win->rend, 255, 0, 0, 0);
      //SDL_RenderDrawPoint(env->win->rend, 150, 150);
       
        //SDL_RenderDrawPoint(env->win->rend, 10, 150);
         SDL_SetRenderDrawColor(env->win->rend, 255, 0, 0, 0);

        SDL_RenderDrawPoint(env->win->rend, 200, 200);
       
        trace(env);
        SDL_RenderPresent(env->win->rend);
        //SDL_UpdateWindowSurface(env->win->handle);

        if (event(env) == 0)
            env->boucle = 1;
    }
    
    
    quit_SDL(env);
    return (0); 
}
