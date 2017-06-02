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

void        trace(t_env *env)
{
    int x;
    int y;
    t_vect *v;
    t_ray *r;
    t_obj *tmp;
    t_hit_point *hp;
    t_cone *cone;
    tmp = env->obj;
        x = 0;
        while (x < env->size_x)
        {
            y = 0;
            while (y < env->size_y)
            {
                env->x = x;
                env->y = y;
                v = new_vect(x, y, 0.0);

                r = new_ray(env->cam->pos, normed_vect(minus_vect(v, env->cam->pos)), norm(minus_vect(env->cam->pos, v)), NULL);
                    if (tmp->form == 4)
                    {
                        cone = (t_cone *)tmp->type;
                        if ((x == 300 && y == 250))
                        {
                            //ft_putnbr(minus_vect(v, env->cam->pos)->x);
                            //ft_putnbr( 10 * normed_vector(minus_vect(v, env->cam->pos))->y);
                            //ft_putchar('\n');
                            //ft_putnbr((int)norm(minus_vect(v, env->cam->pos)));
                            //ft_putchar('\n');
                         if ((hp = hit_cone(cone, r)))
                            SDL_RenderDrawPoint(env->win->rend, x, y);
                            if (x == 500 && y == 380 && !hp)
                                 ft_putstr("ffe");
                           
                    }
                    }
                    free(r);
                y++;
            }
            x++;
        }
        //SDL_RenderPresent(env->win->rend);
        //SDL_UpdateWindowSurface(env->win->handle);
}



void        trace3(t_env *env)
{
    int p;
    int q;
    float min;

    t_vect *v;
    t_ray *r;


    float sum;
    int nb;
    sum = 900.0;
    nb = 0;
    t_vect *color;
    t_obj *tmp;
    t_obj *colore;
    t_hit_point *hp;
    t_hit_point *hr;
    t_hit_point *mem;
    int meet_object;
    float sum1;
    float sum2;
    int nb1;
    int nb2;
    sum1 = 0.0;
    sum2 = 0.0;
    nb1 = 0;
    nb2 = 0;
    tmp = env->obj;
     //SDL_SetRenderDrawColor(env->win->rend, 255, 0, 0, 0);
    //SDL_RenderDrawPoint(env->win->rend, 100, 100);
        p = 0;
        while (p < env->size_x)
        {
            q = 0;
            
            while (q < env->size_y)
            {   
                min = INFINI;
                tmp = env->obj;
                v = new_vect(p, q, 0);
            
                r = new_ray(env->cam->pos, normed_vect(minus_vect(v, env->cam->pos)), norm(minus_vect(env->cam->pos, v)), new_vect(0.0, 0.0, 0.0));
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
                if (min < INFINI && mem)
                {
                    
                    meet_object = 0;
                    r = new_ray(mem->vect, normed_vect(minus_vect(env->light->pos, mem->vect)), 0.0, new_vect(0.0, 0.0, 0.0));
                    
                    while (tmp && !meet_object)
                    {   
                         
                         if (!(hr = tmp->is_hit(tmp->type, r)))
                         {
                              tmp = tmp->next;
                         }
                         else
                         {
                            meet_object = 1;
                         }  
                    }
                    if (!meet_object || (hr && hp && distance(hp->vect, hr->vect) < 15))
                    {
                    color = find_color(env, mem, colore->mater);
                    //SDL_SetRenderDrawColor(env->win->rend, (int)color->x + colore->mater->ir/4, (int)color->y + colore->mater->ir/4, (int)color->z + colore->mater->ir/4, 0);
                            SDL_SetRenderDrawColor(env->win->rend, (int)color->x, (int)color->y, (int)color->z, 0);
                            SDL_RenderDrawPoint(env->win->rend, p, q);
                    }
                    else 
                    {
                        SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
                            SDL_RenderDrawPoint(env->win->rend, p, q);
                    }
                        /*if (!meet_object)
                        {
                            color = find_color(env, mem, colore->mater);
                            //SDL_SetRenderDrawColor(env->win->rend, (int)color->x + colore->mater->ir/4, (int)color->y + colore->mater->ir/4, (int)color->z + colore->mater->ir/4, 0);
                            SDL_SetRenderDrawColor(env->win->rend, (int)color->x, (int)color->y, (int)color->z, 0);
                            SDL_RenderDrawPoint(env->win->rend, p, q);
                         }
                         else
                         {
                               SDL_SetRenderDrawColor(env->win->rend, colore->mater->ir/4, colore->mater->ig/4, colore->mater->ib/4, 0);
                                SDL_RenderDrawPoint(env->win->rend, p, q);
                         }*/
                    tmp = env->obj;
                }
               q++;
             }
               p++;    
            }
        
        //SDL_UpdateWindowSurface(env->win->handle);
}

void        trace2(t_env *env)
{
    int p;
    int q;
    int x1;/*abscisse du pixel dans l'ecran virtuel*/
    int y1;/*ordonnee du pixel dans l'ecran virtuel*/
    int z1;/*altitude du pixel dans l'ecran virtuel*/
    float min;

    t_vect *v;
    t_ray *r;
   
    t_obj *tmp;
    t_obj *colore;
    t_hit_point *hp;
    
    tmp = env->obj;
    
    p = 0;
        while (p < env->size_x)
        {
            q = 0;
            
            while (q < env->size_y)
            {   
                min = INFINI;
                x1 = env->screen->center->x - (env->size_x / 2) * env->screen->v->x - (env->size_y / 2) * env->screen->w->x + p * env->screen->v->x + \
            q * env->screen->w->x;
            y1 = env->screen->center->y - (env->size_x / 2) * env->screen->v->y - (env->size_y / 2) * env->screen->w->y + p * env->screen->v->y \
             + q * env->screen->w->y;
             z1 = env->screen->center->z - (env->size_x / 2) * env->screen->v->z - (env->size_y / 2) * env->screen->w->z + p * env->screen->v->z \
              + q * env->screen->w->z;
              
                v = new_vect(x1, y1, z1);
                r = new_ray(env->cam->pos, normed_vect(minus_vect(v, env->cam->pos)), norm(minus_vect(env->cam->pos, v)), new_vect(0.0, 0.0, 0.0));
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
                        SDL_SetRenderDrawColor(env->win->rend, colore->mater->ir, colore->mater->ig, colore->mater->ib, 0);
                    }
                    tmp = tmp->next;
                    }
                }
                if (min < INFINI)
                        SDL_RenderDrawPoint(env->win->rend, p, q);
                    q++;
             }
                p++;
            }
            
        
        SDL_RenderPresent(env->win->rend);
        //SDL_UpdateWindowSurface(env->win->handle);
}


int main(int argc, char **argv)
{
    t_env *env;
    t_win *win;

 
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
        //ft_putstr("repas");
    /*Placement de l'ecran virtuel*/
    
    //set_virtual_screen(env);


    /*t_vect *v1;
    t_vect *norm;
    t_cone *c;

    if (!(v1 = new_vect(450.0, 350.0, 200.0)))
        return (0);
   
    if (!(norm = new_vect(10.0, 10.0, 10.0)))
        return (0);
    if (!(c = new_cone(v1, norm, 10.0)))
        return (0);*/
       
    SDL_CreateWindowAndRenderer(win->width, win->height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &win->handle, &win->rend);
    SDL_SetRenderDrawColor(env->win->rend, 255, 0, 0, 0);
    SDL_RenderClear(env->win->rend);
	 SDL_SetWindowTitle(win->handle, "RTV1");
     //SDL_SetRenderDrawColor(env->win->rend, 0, 0, 255, 0);
    
     trace3(env);
     //printf("%f", tan(30));
     SDL_RenderPresent(env->win->rend);
     while(!env->boucle)
    {
       
    //On met le fond en couleur
       
    //Couleur de dessin :
        //SDL_SetRenderDrawColor(env->win->rend, 50, 50, 50, 255);

        //SDL_GetWindowSize(env->win->handle, size_x, size_y);
       //SDL_GetWindowPosition(env->win->handle, pos_x, pos_y);
       
       //SDL_SetRenderDrawColor(env->win->rend, 255, 0, 0, 0)
       
        //trace2(env);
        //SDL_RenderPresent(env->win->rend);
        //SDL_UpdateWindowSurface(env->win->handle);
        if (event(env) == 0)
            env->boucle = 1;
    }
    
    
    quit_SDL(env);
    return (0); 
}
