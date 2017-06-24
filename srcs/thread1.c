#include "rtv1.h"
#include <pthread.h>
 

int         ThreadFunction(void* addr)
{
    t_arg   *arg;
    int pmin;
	int pmax;

    arg = (t_arg *)addr;
    pmin = (int) (arg->i * (arg->env->size_x / NB_THREAD));
	pmax = (int) ((arg->i + 1) * (arg->env->size_x / NB_THREAD));
    raytrace_thread(arg->env, pmin, pmax);
    return (1);
}


void			malloc_arg(t_arg *arg, void *a)
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
    malloc_arg(arg, env);
    ct = 0;
    while (ct < NB_THREAD)
    {
        testThread = SDL_CreateThread(ThreadFunction, "Thread", (void*)&arg[ct]);
        SDL_WaitThread(testThread, NULL);
        //SDL_KillThread(testThread);
        ct++;
    }
}


 
/*static void			*thread_fonc(void *b)
{
	t_arg *arg;
	int pmin;
	int pmax;
	arg = (t_arg *)b;
	pmin = (int) (arg->i * (arg->env->size_x / NB_THREAD));
	pmax = (int) ((arg->i + 1) * (arg->env->size_x / NB_THREAD));
	//pthread_mutex_lock(&new_data.mutex);
	raytrace_thread(arg->env, pmin, pmax);
	//pthread_mutex_unlock(&new_data.mutex);
	pthread_exit(NULL);
}

static void			create_thread(pthread_t **thread, int count, t_arg *arg)
{
	int			ret;
	
	while (--count != -1)
	{
		ret = pthread_create(thread[count], NULL,
			thread_fonc, &arg[count]);	
    }
}*/

/*void				redraw(t_env *env, t_arg *arg)
{
	int		i;
	void	*ret;

	i = -1;
	
	create_thread(env->thread, env->thread_cnt, arg);
	
	while (env->thread[++i])
	{
		pthread_join(*env->thread[i], &ret);
	}
}*/
