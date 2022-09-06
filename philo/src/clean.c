/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   clean.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/06 12:00:50 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/06 14:32:35 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	clean_mutexes(t_mutex **mutexes, int32_t count)
{
	int32_t	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&(*mutexes)[i]);
		i++;
	}
	*mutexes = NULL;
	return (ERROR);
}

int32_t deallocate_memory(t_shared *shared, pthread_t **philosophers)
{
	if (shared->philos)
	{
		free(shared->philos);
		shared->philos = NULL;
	}
	if (*philosophers)
	{
		free(*philosophers);
		*philosophers = NULL;
	}
	if (shared->mutexes)
	{
		free(shared->mutexes);
		shared->mutexes = NULL;
	}
	return (ERROR);
}

int32_t	clean_shared(t_shared *shared, pthread_t **philosophers, int32_t count)
{
	clean_mutexes(&shared->mutexes, MUTEX + count);
	deallocate_memory(shared, philosophers);
	return (ERROR);
}

int32_t	join_philosophers(pthread_t *philosophers, int32_t count)
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

int32_t	clean_program(t_shared *shared, pthread_t **philosophers, int32_t count)
{
	join_philosophers(*philosophers, count);
	clean_shared(shared, philosophers, count);
	return (SUCCESS);
}
