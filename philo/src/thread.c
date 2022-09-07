/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   thread.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:08:07 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/07 18:01:19 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <assert.h>

int32_t	join_thread(pthread_t *thread)
{
	if (pthread_join(*thread, NULL))
		return (ERROR);
	return (SUCCESS);
}

int32_t	make_thread(pthread_t *thread, void *(*routine)(void *), void *ptr)
{
	if (pthread_create(thread, NULL, routine, ptr))
		return (ERROR);
	return (SUCCESS);
}

int32_t	breed_philosophers(t_shared *shared, pthread_t **philosophers)
{
	int32_t	i;

	i = 0;
	pthread_mutex_lock(&shared->mutexes[BREED]);
	while (i < shared->cnf.nb_philo)
	{
		if (make_thread(&(*philosophers)[i], philosopher, &shared->philos[i]))
		{
			pthread_mutex_lock(&shared->mutexes[MUTERROR]);
			shared->error = true;
			pthread_mutex_unlock(&shared->mutexes[MUTERROR]);
			pthread_mutex_unlock(&shared->mutexes[BREED]);
			return (join_philosophers(*philosophers, i));
		}
		i++;
	}
	pthread_mutex_lock(&shared->mutexes[START]);
	shared->start = true;
	shared->start_time = time_in_ms();
	pthread_mutex_unlock(&shared->mutexes[START]);
	pthread_mutex_unlock(&shared->mutexes[BREED]);
	return (SUCCESS);
}
