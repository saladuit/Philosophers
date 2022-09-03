/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   mutex.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:09:26 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/03 18:43:46 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <assert.h>

int32_t	mutex_api(t_mutex *mutex, int32_t (*func) (void *), void *ptr)
{
	int32_t	result;

	if (pthread_mutex_lock(mutex))
		return (ERROR);
	result = func(ptr);
	if (pthread_mutex_unlock(mutex))
		return (ERROR);
	return (result);
}

int32_t	init_mutexes(t_mutex *mutexes, int32_t count)
{
	int32_t	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&mutexes[i], NULL))
			return (destroy_mutexes(mutexes, i));
		i++;
	}
	return (SUCCESS);
}

int32_t	destroy_mutexes(t_mutex *mutexes, int32_t count)
{
	int32_t	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
	return (ERROR);
}
