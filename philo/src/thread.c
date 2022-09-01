/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   thread.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:08:07 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/01 22:06:04 by safoh        \___)=(___/                 */
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

int32_t	clean_philosophers(t_shared *shared)
{
	int32_t	i;

	i = 0;
	while (i < shared->count)
	{
		if (join_thread(&shared->philosophers[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int32_t	make_thread(void *(*routine)(void *), void *shared, pthread_t *thread)
{

	if (pthread_create(thread, NULL, routine, shared))
		return (ERROR);
	return (SUCCESS);
}

int32_t	breed_philosophers(t_shared *shared)
{
	int32_t	i;

	i = 0;
	
	if (pthread_mutex_lock(&shared->mutexes[START]))
		return (ERROR);
	while (i < shared->count)
	{
		if (make_thread(philosopher, shared, &shared->philosophers[i]) == ERROR)
		{
			shared->dead = true;
			if (pthread_mutex_unlock(&shared->mutexes[START]))
				return (pthread_create_failed(shared->philosophers, i));
			return (pthread_create_failed(shared->philosophers, i));
		}
		i++;
	}
	shared->start = true;
	if (pthread_mutex_unlock(&shared->mutexes[START]))
		return (ERROR);
	return (SUCCESS);
}
