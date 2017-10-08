#include "rtv1.h"
#include <pthread.h>
 

int         ThreadFunction(void* addr)
{
    t_arg   *arg;
    int pmin;
	int pmax;

    arg = (t_arg *)addr;
    pmin = (int) (arg->i * (arg->env->screen->nx / NB_THREAD));
	pmax = (int) ((arg->i + 1) * (arg->env->screen->nx / NB_THREAD));
    raytrace_thread(arg->env, pmin, pmax);
    return (1);
}


void			fill_arg(t_arg *arg, void *a)
{
    int ct;

    ct = 0;
	while (ct < NB_THREAD)
	{
		arg[ct].env = a;
		arg[ct].i = ct;
        ct++;
	}
	return ;
}

void        boucle(t_arg *arg, t_env *env)
{
    SDL_Thread  *testThread;
    int ct;
    fill_arg(arg, env);
    ct = 0;
    while (ct < NB_THREAD)
    {
        testThread = SDL_CreateThread(ThreadFunction, "Thread", (void*)&arg[ct]);
        SDL_WaitThread(testThread, NULL);
        //SDL_KillThread(testThread);
        ct++;
    }
}
