/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/01 20:28:29 by safoh        \___)=(___/                 */
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

int32_t	get_id(t_shared *shared)
{
	shared->id++;
	printf("I am philosopher: %d\n", shared->id);
	return (shared->id);
}

int32_t	isdead(t_shared *shared)
{
	return (shared->dead);
}

int32_t	canstart(t_shared *shared)
{
	return (shared->start);
}

void	feast(t_shared *shared)
{
	while (1)
	{

	}
}

void	*philosopher(void *p)
{
	t_shared	*shared;
	int32_t		start;
//	int32_t		id;

	shared = (t_shared *)p;
	while (1)
	{
		if (mutex_api(&shared->mutexes.start, isdead, shared))
			return (NULL);
		start = mutex_api(&shared->mutexes.start, canstart, shared);
		if (start == ERROR)
			return (NULL);
		if (start == true)
			break ;
	}
//	id = mutex_api(&shared->mutexes.id, get_id, shared);
//	if (id == ERROR)
//		return (NULL);
//	(void)id;
	feast(shared);
	return (NULL);
}

int32_t	philo(char **argv)
{
	t_shared	shared;

	ft_bzero(&shared, sizeof(t_shared));
	if (init_settings(&shared.count, shared.settings, argv) == ERROR)
		return (ERROR);
	if (init_mutexes(&shared.mutexes, shared.count) == ERROR)
		return (destroy_mutexes(&shared.mutexes, shared.count, 4));
	if (breed_philosophers(&shared) == ERROR)
		return (destroy_mutexes(&shared.mutexes, shared.count, 4));
	if (start_diner(&shared) == ERROR)
		return (destroy_mutexes(&shared.mutexes, shared.count, 4));
	destroy_mutexes(&shared.mutexes, shared.count, 4);
	return (SUCCESS);
}
