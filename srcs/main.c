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

#include "../include/rtv1.h"

/*void pause1()
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
	


	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	
    // Double Buffer
	
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	


	 // Création du contexte OpenGL

    contexteOpenGL = SDL_GL_CreateContext(env->win->handle);
    if(contexteOpenGL == NULL)
    {
		printf("SDL_Init failed: %s\n", SDL_GetError());
        ft_putstr("erreur");
        SDL_DestroyWindow(env->win->handle);
        return (-1);
    }*/




    // Boucle principale

  /*  while(!terminer)
    {
        // Gestion des évènements

        SDL_WaitEvent(&evenements);

        if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            terminer = 1;


        // Nettoyage de l'écran

        //glClear(GL_COLOR_BUFFER_BIT);
        //SDL_GL_SwapWindow(env->win->handle);
    }

	
	//SDL_GL_DeleteContext(contexteOpenGL);
    SDL_DestroyRenderer(env->win->rend);
	SDL_DestroyWindow(env->win->handle);
	SDL_Quit();
	return (EXIT_SUCCESS);
}*/

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_W 800
#define WINDOW_H 800
#define PRECISION 0.001
#define PI 3.14159265

int main(GLvoid)
{
    SDL_Window* fenetre;
    SDL_Renderer* renderer;
    SDL_Event   evenements;
    int boucle;
    int *size_x;
    int *size_y;
    int *pos_x;
    int *pos_y;

    size_x = NULL;
    size_y = NULL;
    pos_x = NULL;
    pos_y = NULL;
    boucle = 0;
     fenetre = NULL;
    renderer = NULL;
    if (!(pos_x = (int*)malloc(sizeof(int))))
        return (0);
    if (!(pos_y = (int*)malloc(sizeof(int))))
        return (0);
     if (!(size_x = (int*)malloc(sizeof(int))))
        return (0);
    if (!(size_y = (int*)malloc(sizeof(int))))
        return (0);
    //SDL_Point octogone[9];//Déclaration du tableau contenant les cases blanches
    //SDL_Point ligne_depart,ligne_arrivee;//Déclaration du point de départ et du point d'arrivée d'une ligne

   
     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
        return (0);
   
    SDL_CreateWindowAndRenderer(1000, 700, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &fenetre, &renderer);
    SDL_SetWindowTitle(fenetre, "RTV1");

     while(!boucle)
    {


//On met le fond en couleur
    SDL_SetRenderDrawColor(renderer, 0, 160, 160, 0);
    SDL_RenderClear(renderer);
    
//Couleur de dessin :
    SDL_SetRenderDrawColor(renderer,180,50,0, 255);


    
    SDL_GetWindowSize(fenetre, size_x, size_y);
    SDL_GetWindowPosition(fenetre, pos_x, pos_y);
    for(double i = 0.0; i < 2 * PI; i+= PRECISION)
    {
            SDL_RenderDrawPoint(renderer, *size_x / 2 +  400 * cos(i), *size_y / 2 + 400 * sin(i));
            //SDL_RenderDrawPoint(renderer, 780 , 370);
    }
    SDL_RenderPresent(renderer);
//Maintenant, notre octogone
    /*for(int i = 0; i != 9; i++)
    {
        octogone[i].x = WINDOW_W /2 - cos(i*45*PI/180)*WINDOW_W / 2; //On détermine la position 
        octogone[i].y = WINDOW_H /2 - sin(i*45*PI/180)*WINDOW_H / 2; //de chaque point de l'octogone
    }
    octogone[8] = octogone[0];//Le dernier point rejoint le premier, pour clore le polygone*/

//On trace le chemin formé par les points
   /* if( SDL_RenderDrawLines(renderer, octogone, 9)<0)
    {
        printf("Erreur dans le tracé de l'octogone : %s",SDL_GetError());
        return EXIT_FAILURE;
    }*/

    
       

        SDL_WaitEvent(&evenements);

        
        if (evenements.type == SDL_KEYDOWN && evenements.key.keysym.sym == SDLK_ESCAPE)
				return 0;
		else if (evenements.type == SDL_QUIT)
				return 0;
            /*SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);*/

        else if(evenements.type == SDL_WINDOWEVENT){
            if(evenements.window.event == SDL_WINDOWEVENT_RESIZED) {
                printf("Fenêtre redimensionnée\n"); /* Fenêtre redimensionnée */
            }
            if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
                boucle = 1;
        }
        
            
        // else if (evenements.type == SDL_WINDOWEVENT_RESIZED)
		// {
		// 		//raytrace(e);
		// 		SDL_SetRenderDrawColor(renderer, 160, 160, 160,255);
        //         SDL_RenderClear(renderer);
        //          SDL_SetRenderDrawColor(renderer,255,255,255,255);
        //         for(double i = 0.0; i < 360; i+= PRECISION)
        //             SDL_RenderDrawPoint(renderer, i, i);
        //         SDL_RenderPresent(renderer);
		// 		return 0;
		// }
		else if (evenements.type == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				SDL_RenderClear(renderer);
				return 0;
			}
			
      
    }

    SDL_DestroyWindow(fenetre);
    SDL_Quit(); 
}
