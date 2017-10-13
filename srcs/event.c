/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:54:51 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 18:05:39 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "event.h"

void	refresh(t_env *env, t_arg *arg)
{
	SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
	SDL_RenderClear(env->win->rend);
	boucle(arg, env);
	SDL_UpdateWindowSurface(env->win->handle);
	SDL_RenderPresent(env->win->rend);
}

int		key_event_bis(t_env *env, SDL_Event event)
{
	int		b;

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
		env->cam->add_theta += 5.0 * M_PI / 180.0;
	else if (event.key.keysym.scancode == ROT_THETA_LESS)
		env->cam->add_theta -= 5.0 * M_PI / 180.0;
	else if (event.key.keysym.scancode == ROT_PHI_PLUS)
		env->cam->add_phi += 5.0 * M_PI / 180.0;
	else if (event.key.keysym.scancode == ROT_PHI_LESS)
		env->cam->add_phi -= 5.0 * M_PI / 180.0;
	else
		b = 0;
	return (b);
}

void	key_event(t_env *env, SDL_Event event, t_arg *arg)
{
	int		b;

	b = 1;
	if (event.key.keysym.scancode == RIGHT)
		env->cam->trans.x += 0.1;
	else if (event.key.keysym.scancode == LEFT)
		env->cam->trans.x -= 0.1;
	else if (event.key.keysym.scancode == UP)
		env->cam->trans.y -= 0.1;
	else if (event.key.keysym.scancode == DOWN)
		env->cam->trans.y += 0.1;
	else if (event.key.keysym.scancode == Z_PLUS)
		env->cam->trans.z += 0.1;
	else if (event.key.keysym.scancode == Z_LESS)
		env->cam->trans.z -= 0.1;
	else if (!key_event_bis(env, event))
		b = 0;
	if (b == 1)
		refresh(env, arg);
}

int		event(t_env *env, t_arg *arg)
{
	SDL_Event	event;

	SDL_WaitEvent(&event);
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		return (0);
	else if (event.type == SDL_QUIT)
		return (0);
	else if (event.type == SDL_WINDOWEVENT)
	{
		if (event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 0);
			SDL_RenderClear(env->win->rend);
		}
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			return (0);
	}
	else if (event.type == SDL_WINDOWEVENT_SIZE_CHANGED)
		SDL_RenderClear(env->win->rend);
	else if (event.type == SDL_KEYUP)
		key_event(env, event, arg);
	return (1);
}

void	quit_sdl(t_env *env)
{
	SDL_DestroyRenderer(env->win->rend);
	SDL_DestroyWindow(env->win->handle);
	SDL_Quit();
}
