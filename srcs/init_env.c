/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:10:26 by fgallois          #+#    #+#             */
/*   Updated: 2017/05/15 14:10:30 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"


void        render(t_env *env)            
{
    SDL_Event event;

	

    
	//raytrace(e);
	
	/*SDL_RenderPresent(env->win->rend);*/

	//SDL_SetRenderDrawColor(env->win->rend,0,255,0,255);

	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT_RESIZED)
			{
				//raytrace(e);
				SDL_SetRenderDrawColor(env->win->rend, 255,  255, 255, 255);
				SDL_RenderClear(env->win->rend);
	 			SDL_RenderPresent(env->win->rend);

				return ;
			}
			else if (event.type == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				SDL_SetRenderDrawColor(env->win->rend, 255,  255, 255, 255);
				SDL_RenderClear(env->win->rend);
				 SDL_RenderPresent(env->win->rend);
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

t_env   *init_env(void)
{
    t_env   *env;
    t_win   *win;
    
    if (!(env = malloc(sizeof(t_env))))
        return (NULL);
    if (!(env->win = malloc(sizeof(t_win))))
        return (NULL);
	if (!(env->cam = malloc(sizeof(t_cam))))
        return (NULL);	
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
        return (NULL);
    win = env->win;
    win->width = 900;//1200
    win->height = 700;//900
	env->boucle = 0;
	env->cam->pos = new_vect(450.0, 350.0, -400.0);//new_vect(600.0, 450.0, -400.0);
    //SDL_CreateWindowAndRenderer(win->width, win->height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &win->handle, &win->rend);
	//SDL_SetWindowTitle(win->handle, "RTV1");
 
    return (env);
}
