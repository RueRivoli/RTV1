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
#include <SDL2/SDL.h>
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
	SDL_Window *screen = NULL;
	SDL_Event evenements;
	int boolean = 0;
	SDL_GLContext contexteOpenGL;


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	
    // Double Buffer
	
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	/*Demarrage de la SDL (ici : chargement du systeme video)*/
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		ft_putstr("Erreur d'initialisation de la SDL : %s\n'");
		exit(EXIT_FAILURE);
	}

	if (!(screen = SDL_CreateWindow("Ma fenêtre RTV1", 
                          SDL_WINDOWPOS_UNDEFINED, 
                          SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
	{
			ft_putstr("Impossible de charger le mode video : %s\n");
			exit(EXIT_FAILURE);
	}

	 // Création du contexte OpenGL

    contexteOpenGL = SDL_GL_CreateContext(screen);
	
    if(contexteOpenGL == NULL)
    {
		printf("SDL_Init failed: %s\n", SDL_GetError());
        ft_putstr("erreur");
        SDL_DestroyWindow(screen);

        return -1;
    }

	/*glClearColor(1,1,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(screen);*/
	while(boolean == 0)
    {
		SDL_WaitEvent(&evenements);
		
		if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
	   		 boolean = 1;
    }

	SDL_GL_DeleteContext(contexteOpenGL);
	SDL_DestroyWindow(screen);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
