/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/30 14:21:54 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	ft_check_shared_bool(t_mutex *mutex, bool *input)
{
	bool result;

	result = false;
	pthread_mutex_lock(mutex);
	result = *input;
	pthread_mutex_unlock(mutex);
	if (result == true)
		return (true);
	return (false);
}

int64_t	timeInMilliseconds(void) {
    t_timeval tv;

    gettimeofday(&tv,NULL);
    return ((tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

int64_t	timedifference(t_timeval start, t_timeval end)
{
    return ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec - start.tv_usec) / 1000);
}

void	ft_switch_shared_bool(t_mutex *mutex, bool *input)
{
	pthread_mutex_lock(mutex);
	if (*input == true)
		*input = false;
	else
		*input = true;
	pthread_mutex_unlock(mutex);
}

void	take_fork(t_mutex *fork, time_t time, int32_t id)
{
	pthread_mutex_lock(fork);
	printf("%ld %d has taken a fork\n", time, id);
	pthread_mutex_unlock(fork);
}

int16_t	get_id(t_mutex *id_lock, int32_t *shared_id)
{
	int16_t	id;

	pthread_mutex_lock(id_lock);
	(*shared_id)++;
	id = *shared_id;
	printf("I am philosopher: %d\n", id);
	pthread_mutex_unlock(id_lock);
	return (id);
}

int32_t	mutex_api(t_mutex *mutex, int32_t (*f) (void *), void *data)
{
	int32_t	result;

	pthread_mutex_lock(mutex);
	result = f(data);
	pthread_mutex_unlock(mutex);
	return (result);
}

void	take_forks(t_shared *shared)
{
	t_shared *p
	take_fork(shared->mutexes->forks);
}

void	*philosopher(void *p) {
	t_shared	*shared;
	int16_t		id;
	t_timeval start;

	shared = (t_shared *)p;
	while (!ft_check_shared_bool(&shared->mutexes.start, &shared->start))
		continue ;
	id = get_id(&shared->mutexes.id, &shared->id);
	take_forks(&shared);
	return (NULL);
}

int32_t	philo(char **argv)
{
	t_shared	shared;

	if (init_settings(&shared.settings, argv) == ERROR)
		return (ERROR);
	if (init_mutexes(&shared.mutexes, shared.count) == ERROR)
		return (ERROR);
	if (breed_philosophers(&shared) == ERROR)
		return (ERROR);
	if (start_diner(&shared) == ERROR)
		return (ERROR);
	destroy_mutexes(&shared.mutexes, shared.count, 4);
}
