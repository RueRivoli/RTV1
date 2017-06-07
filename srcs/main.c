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
#   include "../include/event.h"
# include <SDL2/SDL.h>
# include <stdlib.h>
#include <stdio.h>
# include <math.h>

void        refresh(t_env *env)
{
            SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
	        SDL_RenderClear(env->win->rend);
            raytrace(env);
	        SDL_RenderPresent(env->win->rend);
}

int        event(t_env *env)
{
    SDL_Event   event;
    //SDL_KeyboardEvent *key;
    SDL_WaitEvent(&event);
    //SDL_PollEvent(&event);

   
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                    return (0);
	else if (event.type == SDL_QUIT)
                    return (0);
        else if (event.type == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
                SDL_RenderClear(env->win->rend);
                  //return (0);
            }
           if(event.window.event == SDL_WINDOWEVENT_CLOSE)
                return (0);
        }
	     else if (event.type == SDL_WINDOWEVENT_SIZE_CHANGED)
	     		SDL_RenderClear(env->win->rend);
        else if (event.type == SDL_KEYUP)
         {
            ft_putnbr(event.key.keysym.scancode);
            if (event.key.keysym.scancode == RIGHT)
            {
                env->cam->trans->x += 125.0;
                refresh(env);
            }
            if (event.key.keysym.scancode == LEFT)
            {
                env->cam->trans->x -= 125.0;
                refresh(env);
            }
            if (event.key.keysym.scancode == UP)
            {
                env->cam->trans->y -= 125.0;
                refresh(env);
            }
            if (event.key.keysym.scancode == DOWN)
            {
                env->cam->trans->y += 125.0;
                refresh(env);
            }
            if (event.key.keysym.scancode == Z_PLUS)
            {
                env->cam->trans->z += 125.0;
                refresh(env);
            }
            if (event.key.keysym.scancode == Z_LESS)
            {
                env->cam->trans->z -= 125.0;
                refresh(env);
            }
            if (event.key.keysym.scancode == RESET)
            {
                env->cam->trans->x = 0.0;
                env->cam->trans->y = 0.0;
                env->cam->trans->z = 0.0;
                env->cam->add_phi = 0.0;
                env->cam->add_theta = 0.0;
                refresh(env);
            }
            if (event.key.keysym.scancode == ROT_THETA_PLUS)
            {
                env->cam->add_theta += 10.0;
                refresh(env);
            }
            if (event.key.keysym.scancode == ROT_THETA_LESS)
            {
                env->cam->add_theta -= 10.0;
                refresh(env);
            }
            if (event.key.keysym.scancode == ROT_PHI_PLUS)
            {
                env->cam->add_phi += 10.0;
                refresh(env);
            }
            if (event.key.keysym.scancode == ROT_PHI_LESS)
            {
                env->cam->add_phi -= 10.0;
                refresh(env);
            }
            }
            else if (event.type == SDLK_DOWN)
            {
                   ft_putnbr(event.key.keysym.scancode);
            }
     return (1);
 }

void        quit_SDL(t_env *env)
{
    SDL_DestroyRenderer(env->win->rend);
    SDL_DestroyWindow(env->win->handle);
    SDL_Quit();
}


void        raytrace(t_env *env)
{
    int p;
    int q;
    float min;

    t_vect *v;
    t_vect *col;
    t_ray *r;
    //t_vect *color;
    t_obj *tmp;
    t_obj *colore;
    t_hit_point *hp;
    t_hit_point *hr;
    t_hit_point *mem;
    t_light *light;
    int red;
    int green;
    int blue;
    int meet_object;
    int nb_of_lights;
    float a;
    float b;
    float c;
    float me;
    me = 0.0;
    a = 0.0;
    b = 0.0;
    c = 0.0;
    tmp = env->obj;
    env->cam->pos = add_vect(env->cam->pos, env->cam->trans);
        p = 0;
        while (p < env->size_x)
        {
            q = 0;
            
            while (q < env->size_y)
            {   
                min = INFINI;
                tmp = env->obj;
                a = p + env->cam->trans->x;
                b = q + env->cam->trans->y;
                c = env->cam->trans->z;
                me = a;
                /*a = cos(env->cam->rot->z * M_PI / 180) * a + sin(env->cam->rot->z * M_PI / 180) * b;
                b = -sin(env->cam->rot->z * M_PI / 180) * me + cos(env->cam->rot->z * M_PI / 180) * b;
                me = b;
                b = cos(env->cam->rot->x * M_PI / 180) * b + sin(env->cam->rot->x * M_PI / 180) * c;
                c = -sin(env->cam->rot->x * M_PI / 180) * me + cos(env->cam->rot->x * M_PI / 180) * c;
                me = c;
                c = cos(env->cam->rot->y * M_PI / 180) * c + sin(env->cam->rot->y * M_PI / 180) * a;
                a = -sin(env->cam->rot->y * M_PI / 180) * me + cos(env->cam->rot->y * M_PI / 180) * a;*/

                v = new_vect(p + a, q + b, c);
                r = new_ray(env->cam->pos, normed_vect(minus_vect(v, env->cam->pos)), norm(minus_vect(env->cam->pos, v)), new_vect(0.0, 0.0, 0.0));
                find_angle(env, r);
                free(v);
                while (tmp)
                {   
                     
                    if (!(hp = tmp->is_hit(tmp->type, r)))
                    {                                        
                            tmp = tmp->next;
                    }
                    else 
                    {
                          hp->distance_to_cam = distance_with_cam(env, hp);
                          if (hp->distance_to_cam < min)
                          {
                                min = hp->distance_to_cam;
                                colore = tmp;
                                mem = hp;
                            //SDL_SetRenderDrawColor(env->win->rend, colore->mater->ir, colore->mater->ig, colore->mater->ib, 0);
                          }
                         tmp = tmp->next;
                      }
                }
                tmp = env->obj;
                free(r);
                if (min < INFINI && mem)
                {   
                    light = env->light;
                    red = 0;
                    blue = 0;
                    green = 0;
                    nb_of_lights = numberoflights(env);
                    col = new_vect(0.0, 0.0, 0.0);
                    while (light)
                    {   
                
                        meet_object = 0;
                        r = new_ray(mem->vect, normed_vect(minus_vect(light->pos, mem->vect)), 0.0, new_vect(0.0, 0.0, 0.0));
                        tmp = env->obj;
                        while (tmp && !meet_object)
                         {   
                              if (tmp == colore)
                                    tmp = tmp->next;
                             else if (!(hr = tmp->is_hit(tmp->type, r)))
                                 tmp = tmp->next;
                             else
                             {
                                if (distance(mem->vect, hr->vect) < distance(hr->vect, light->pos))
                                {    
                                    meet_object = 1;
                                    hr->distance_to_cam = distance_with_cam(env, hr);
                                }
                                else
                                    tmp = tmp->next;
                            }
                        }
                        free(r);
                         if (!meet_object)
                         {
                                //color = find_color(env, mem, colore->mater);  
                                 //if ((int)color->x == 0)
                               //  color->x = 1;
                                 col = find_color_light(light, mem, colore->mater, col);
                                 
                               //  SDL_SetRenderDrawColor(env->win->rend, (int)color->x, (int)color->y, (int)color->z, 0);
                              //SDL_RenderDrawPoint(env->win->rend, p, q);
                         }
                         else
                         {
                                  col = find_color_sha(light, mem, colore->mater, col);
                              //if ((int)color->x == 0)
                                  //  color->x = 1;
                                   
                            //SDL_SetRenderDrawColor(env->win->rend, (int)(color->x / 2), (int) (color->y / 2), (int) (color->z / 2), 0);
                            //SDL_SetRenderDrawColor(env->win->rend, (int)color->x, (int) color->y, (int) color->z, 0);
                           //SDL_RenderDrawPoint(env->win->rend, p, q);
                           }
                           light = light->next;
                            
                       }
                           SDL_SetRenderDrawColor(env->win->rend, (int)col->x / (255 * nb_of_lights), (int)col->y / (255 * nb_of_lights), (int)col->z / (255 * nb_of_lights), 0);
                           SDL_RenderDrawPoint(env->win->rend, p, q);
                           free(col);
                    }
               q++;
             }
               p++;    
            }
    
}

void            SDL_render(t_env *env)
{
    SDL_Event event;

    SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
	SDL_RenderClear(env->win->rend);
	raytrace(env);
	SDL_RenderPresent(env->win->rend);
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT_RESIZED)
			{
				raytrace(env);
				SDL_RenderClear(env->win->rend);
				return ;
			}
			else if (event.type == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				SDL_RenderClear(env->win->rend);
				return ;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				return ;
			}
			else if (event.type == SDL_QUIT)
				return ;
		}
	}
}
  

int              main(int argc, char **argv)
{
    t_env *env;
    t_win *win;
    int b;
    b = 1;
 
    int fd;
    
    if (!(env = init_env()))
        return (0);
         win = env->win;
    if (argc != 2)
    {
        error_param();
        return (0);
    }

    fd = open(argv[1], O_RDONLY);

    /*Lecture et affichage de la scene*/
    if (lecture(fd, env) != 0)
        display_scene(env);
    /*Placement de l'ecran virtuel*/
    
    //set_virtual_screen(env);

    SDL_CreateWindowAndRenderer(win->width, win->height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &win->handle, &win->rend);
    SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
    SDL_RenderClear(env->win->rend);
	SDL_SetWindowTitle(win->handle, "RTV1");

     
     SDL_RenderClear(env->win->rend);
    raytrace(env);
	SDL_RenderPresent(env->win->rend);
     while(!env->boucle)
    {
        if (event(env) == 0)
            env->boucle = 1;
    }
    quit_SDL(env);
    return (0); 
}
