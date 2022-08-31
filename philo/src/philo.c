/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/31 18:54:15 by saladuit     \___)=(___/                 */
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

int32_t	can_i_eat(t_shared *shared)
{
	return (shared->start);
}

void	*philosopher(void *p)
{
	t_shared	*shared;
	int32_t		id;

	shared = (t_shared *)p;
	mutex_api(&shared->mutexes.start, NULL, NULL);
	id = mutex_api(&shared->mutexes.id, get_id, shared);
	(void)id;
	return (NULL);
}

int32_t	philo(char **argv)
{
	t_shared	shared;

	if (init_settings(&shared.count, shared.settings, argv) == ERROR)
		return (ERROR);
	if (init_mutexes(&shared.mutexes, shared.count) == ERROR)
		return (ERROR);
	pthread_mutex_lock(&shared.mutexes.start);
	if (breed_philosophers(&shared) == ERROR)
		return (ERROR);
	pthread_mutex_unlock(&shared.mutexes.start);
	if (start_diner(&shared) == ERROR)
		return (ERROR);
	destroy_mutexes(&shared.mutexes, shared.count, 4);
	return (SUCCESS);
}
