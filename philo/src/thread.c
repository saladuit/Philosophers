/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   thread.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:08:07 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/06 12:46:59 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <assert.h>

void	ft_switch_bool(bool *input)
{
	if (*input == true)
		*input = false;
	else
		*input = true;
}

int32_t	join_thread(pthread_t *thread)
{
	if (pthread_join(*thread, NULL))
		return (ERROR);
	return (SUCCESS);
}

int32_t	pthread_create_failed(pthread_t *philosophers, int32_t count)
{
	int32_t	i;

	i = 0;
	while (i < count)
	{
		join_thread(&philosophers[i]);
		i++;	
	}
	return (ERROR);
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
	if (pthread_mutex_lock(&shared->mutexes[BREED]))
		return (ERROR);
	while (i < shared->cnf.nb_philo)
	{
		if (make_thread(&(*philosophers)[i], philosopher, shared) == ERROR)
		{
			pthread_mutex_lock(&shared->mutexes[DEAD]);
			shared->dead = true;
			pthread_mutex_unlock(&shared->mutexes[DEAD]);
			pthread_mutex_unlock(&shared->mutexes[BREED]);
			return (join_philosophers(*philosophers, i));
		}
		i++;
	}
	if (pthread_mutex_lock(&shared->mutexes[START]))
		return (ERROR);
	shared->start = true;
	shared->start_time = time_in_ms();
	if (pthread_mutex_unlock(&shared->mutexes[START]))
		return (ERROR);
	if (pthread_mutex_unlock(&shared->mutexes[BREED]))
		return (ERROR);
	return (SUCCESS);
}
