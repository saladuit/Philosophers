/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/01 22:09:31 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>


int64_t	timeInMilliseconds(void) {
    t_timeval tv;

    gettimeofday(&tv,NULL);
    return ((tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

int64_t	timedifference(t_timeval start, t_timeval end)
{
    return ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec - start.tv_usec) / 1000);
}

//void	take_fork(t_mutex *fork, time_t time, int32_t id)
//{
//	pthread_mutex_lock(fork);
//	printf("%ld %d has taken a fork\n", time, id);
//	pthread_mutex_unlock(fork);
//}
//
//void	take_forks(t_shared *shared)
//{
//	t_shared *p;
//	take_fork(shared->mutexes.forks);
//}

int32_t	get_id(void *ptr)
{
	int32_t	id;
	
	((t_shared *)ptr)->id++;
	id = ((t_shared *)ptr)->id;
	((t_shared *)ptr)->settings[id].id = id;
	return (((t_shared *)ptr)->id);
}

int32_t	isdead(void *ptr)
{
	return (((t_shared *)ptr)->dead);
}

int32_t	canstart(void *ptr)
{
	return (((t_shared *)ptr)->start);
}

void	narrator(int64_t time, int32_t id, char *str)
{
	printf("%lld\t%d\t%s\n", time, id, str);
}

int32_t	eat(void *ptr)
{
	narrator(timeInMilliseconds(), ((t_philo *)ptr)->id, EATING);
	return (0);
}

int32_t died(void *ptr)
{
	narrator(timeInMilliseconds(), ((t_philo *)ptr)->id, DIED);
	return (0);
}
void	start_feasting(t_shared *shared)
{
	int32_t	id;
	id = mutex_api(&shared->mutexes[ID], get_id, shared);
	if (id == ERROR)
		return ;
	while (1)
	{
		if (mutex_api(&shared->mutexes[VOICE], eat, &shared->settings[id]))
			return ;
	}
}

void	*philosopher(void *p)
{
	t_shared	*shared;
	int32_t		start;

	shared = (t_shared *)p;
	while (1)
	{
		if (mutex_api(&shared->mutexes[START], isdead, shared))
			return (NULL);
		start = mutex_api(&shared->mutexes[START], canstart, shared);
		if (start == ERROR)
			return (NULL);
		if (start == true)
			break ;
	}
	start_feasting(shared);
	return (NULL);
}

void	monitor_philosophers(t_shared *shared)
{
	int32_t	i;

	i = 0;
	while (1)
	{
		while (i < shared->count)
		{
		if (mutex_api(&shared->mutexes[DEAD], isdead, shared))
			if (mutex_api(&shared->mutexes[VOICE], died, shared))
				return ;
		i++;
		}
	}
}

int32_t	philo(char **argv)
{
	t_shared	shared;

	ft_bzero(&shared, sizeof(t_shared));
	if (init_settings(&shared.count, shared.settings, argv) == ERROR)
		return (ERROR);
	if (init_mutexes(shared.mutexes, shared.count + EXTRA_MUTEXES) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.count + EXTRA_MUTEXES));
	if (breed_philosophers(&shared) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.count + EXTRA_MUTEXES));
	monitor_philosophers(&shared);
	if (clean_philosophers(&shared) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.count + EXTRA_MUTEXES));
	destroy_mutexes(shared.mutexes, shared.count + EXTRA_MUTEXES);
	return (SUCCESS);
}
