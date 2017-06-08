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

int            find_nearest_inter(t_env *env, t_vect *v, t_hit_point **mem, t_obj **colore)
{
    t_vect *mini;
    t_vect *w;
    t_vect *ray_dir;
    t_obj *tmp;
    t_hit_point *hp;
    t_ray *r;
    float min;

    tmp = env->obj;
    min = INFINI;
    mini = minus_vect(v, env->cam->pos);
    w = new_vect(0.0, 0.0, 0.0);
    ray_dir = normed_vect(mini);
    r = new_ray(env->cam->pos, ray_dir, norm(mini), w);
    while (tmp)
   {   
                     
                    if (!(hp = tmp->is_hit(tmp->type, r)))
                            tmp = tmp->next;
                    else 
                    {
                          hp->distance_to_cam = distance_with_cam(env, hp);
                          if (hp->distance_to_cam < min)
                          {
                                min = hp->distance_to_cam;
                                *colore = tmp;
                                *mem = hp;
                            
                          }
                         tmp = tmp->next;
                      }
   }
                tmp = env->obj;
                free(v);
                free(mini);
                free(ray_dir);
                free(w);
                free(r);
                return (min);
}

  int        is_light_reached(t_light *light, t_env *env, t_hit_point *mem, t_obj *colore)
    {
                    t_vect *mini;
                    t_vect *v;
                    t_vect *w;
                    t_vect *ray_dir;
                    t_ray *r;
                    t_obj *tmp;
                    t_hit_point *hr;
                    int meet_object;
                
                    meet_object = 0;
                        mini = minus_vect(light->pos, mem->vect);
                        v = normed_vect(mini);
                        w = new_vect(0.0, 0.0, 0.0);
                        ray_dir = normed_vect(mini);
                        r = new_ray(mem->vect, v, 0.0, w);
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
                                    return (1);
                                tmp = tmp->next;
                                free(hr);
                            }
                        }
                        
                        free(r);
                        free(v);
                        free(mini);
                        free(ray_dir);
                         free(w);
                         return (0);
   }

 void               put_on_light(t_env *env, t_hit_point *mem, t_obj *colore, int p, int q)
{
                    float nb_of_lights;
                    t_light *light;
                    t_vect *col;
                    int meet_object;
                    light = env->light;
                    nb_of_lights = numberoflights(env);
                    col = new_vect(0, 0, 0);
                    while (light)
                    {   
                        meet_object = is_light_reached(light, env, mem, colore);
                        
                         if (!meet_object)
                         {
                             
                                 //if ((int)color->x == 0)
                               //  color->x = 1;
                                 col = find_color_light(light, mem, colore->mater, col);
                                 
                         }
                         else
                         {
                             //if ((int)color->x == 0)
                                  //  color->x = 1;
                                  col = find_color_sha(light, mem, colore->mater, col);
                           }
                           light = light->next;
                       }
                       SDL_SetRenderDrawColor(env->win->rend, (int)col->x / (255 * nb_of_lights), (int)col->y / (255 * nb_of_lights), (int)col->z / (255 * nb_of_lights), 0);
                       SDL_RenderDrawPoint(env->win->rend, p, q);
                    
}


void        raytrace(t_env *env)
{
    int p;
    int q;
    float min;
    t_vect *v;
    t_obj *tmp;
    t_obj *colore;

    t_hit_point *mem;
    t_light *light;

    int nb_of_lights;


    tmp = env->obj;
    colore = NULL;

    env->cam->pos = add_vect(env->cam->pos, env->cam->trans);
    mem = malloc(sizeof(t_hit_point*));
    nb_of_lights = numberoflights(env);
        p = 0;
        while (p < env->size_x)
        {
            q = 0;
            
            while (q < env->size_y)
            {   

                min = INFINI;
                tmp = env->obj;
                v = new_vect(p + env->cam->trans->x, q + env->cam->trans->y, env->cam->trans->z);
                min = find_nearest_inter(env, v, &mem, &colore);
                if (min < INFINI && mem)
                {   
                    light = env->light;
                    nb_of_lights = numberoflights(env);
                     put_on_light(env, mem, colore, p, q);
                    
                    //free(mem);
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
    free(env->cam);
    free(env->win);
    free(env);
    return (0); 
}
