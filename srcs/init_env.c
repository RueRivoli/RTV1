
#include "rtv1.h"


void        render(t_env *env)            
{
    SDL_Event event;

	SDL_RenderClear(env->win->rend);
	//raytrace(e);
	SDL_RenderPresent(env->win->rend);
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT_RESIZED)
			{
				//raytrace(e);
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

t_env   *init_env(void)
{
    t_env   *env;
    t_win   *win;
    
    if (!(env = malloc(sizeof(t_env))))
        return (NULL);
    if (!(env->win = malloc(sizeof(t_win))))
        return (NULL);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
        return (NULL);
    win = env->win;
    win->width = 800;
    win->height = 500;
    /*if (!(win->handle = SDL_CreateWindow("Ma fenêtre RTV1", 
                          SDL_WINDOWPOS_UNDEFINED, 
                          SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
	{
			ft_putstr("Impossible de charger le mode video : %s\n");
			return (NULL);
    }*/
    SDL_CreateWindowAndRenderer(win->width, win->height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &win->handle, &win->rend);
	SDL_SetWindowTitle(win->handle, "fenetre principale");
    
    return (env);
}
