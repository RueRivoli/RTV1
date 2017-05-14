/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:54:51 by fgallois          #+#    #+#             */
/*   Updated: 2017/05/12 11:11:12 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/rtv1.h"
//#include "../framework/SLD2/include/SDL.h"
#include <SDL.h>
#include "../framework/SDL2/include/SDL.h"
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

void pause1()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}


int		main(void)
{
	t_env		*env;
    SDL_Event evenements;
   // SDL_GLContext contexteOpenGL;

	if (!(env = init_env()))
		return (0);


	//SDL_Window *screen = NULL;
	int terminer = 0;
	


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	
    // Double Buffer
	
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	


	 // Création du contexte OpenGL

    /*contexteOpenGL = SDL_GL_CreateContext(env->win->handle);
    if(contexteOpenGL == NULL)
    {
		printf("SDL_Init failed: %s\n", SDL_GetError());
        ft_putstr("erreur");
        SDL_DestroyWindow(env->win->handle);
        return (-1);
    }*/




    // Boucle principale

    while(!terminer)
    {
        // Gestion des évènements

        SDL_WaitEvent(&evenements);

        if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            terminer = 1;


        // Nettoyage de l'écran

        glClear(GL_COLOR_BUFFER_BIT);


        SDL_GL_SwapWindow(env->win->handle);
    }

	
	//SDL_GL_DeleteContext(contexteOpenGL);
	SDL_DestroyWindow(env->win->handle);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
