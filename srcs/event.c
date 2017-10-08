/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:54:51 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/09 11:49:49 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "event.h"

void		refresh(t_env *env, t_arg *arg)
{
	SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
	SDL_RenderClear(env->win->rend);
	//raytrace(env);
	//redraw(env, arg);
	//(void)arg;
	boucle(arg, env);
	SDL_UpdateWindowSurface(env->win->handle);
	SDL_RenderPresent(env->win->rend);
}

int    key_event_bis(t_env *env, SDL_Event event)
{
    int b;
    b = 1;
    if (event.key.keysym.scancode == RESET)
    {
		env->cam->trans.x = 0.0;
		env->cam->trans.y = 0.0;
		env->cam->trans.z = 0.0;
		env->cam->add_phi = 0.0;
		env->cam->add_theta = 0.0;
    }
	else if (event.key.keysym.scancode == ROT_THETA_PLUS)
		env->cam->add_theta += 10.0 * M_PI / 180.0;
	else if (event.key.keysym.scancode == ROT_THETA_LESS)
		env->cam->add_theta -= 10.0 * M_PI / 180.0;
	else if (event.key.keysym.scancode == ROT_PHI_PLUS)
		env->cam->add_phi += 10.0 * M_PI / 180.0;
	else if (event.key.keysym.scancode == ROT_PHI_LESS)
		env->cam->add_phi -= 10.0 * M_PI / 180.0;
    else 
        b = 0;
    return (b);
}

void     key_event(t_env *env, SDL_Event event, t_arg *arg)
{
    int b;
    b = 1;
    //ft_putnbr(event.key.keysym.scancode);
	if (event.key.keysym.scancode == RIGHT)
		env->cam->trans.x += 0.02;
	else if (event.key.keysym.scancode == LEFT)
		env->cam->trans.x -= 0.02;
	else if (event.key.keysym.scancode == UP)
		env->cam->trans.y -= 0.02;
	else if (event.key.keysym.scancode == DOWN)
		env->cam->trans.y += 0.02;
	else if (event.key.keysym.scancode == Z_PLUS)
		env->cam->trans.z += 0.01;
	else if (event.key.keysym.scancode == Z_LESS)
		env->cam->trans.z -= 0.01;
    else if (!key_event_bis(env, event))
        b = 0;
    if (b == 1)
        refresh(env, arg);
}

int		event(t_env *env, t_arg *arg)
{
	SDL_Event	event;
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
		key_event(env, event, arg);
	//else if (event.type == SDLK_DOWN)
	//	ft_putnbr(event.key.keysym.scancode);
	return (1);
}

void        quit_SDL(t_env *env)
{
	SDL_DestroyRenderer(env->win->rend);
	SDL_DestroyWindow(env->win->handle);
	SDL_Quit();
}
