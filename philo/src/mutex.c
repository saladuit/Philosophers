/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   mutex.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:09:26 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/30 14:17:31 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	init_mutexes(t_mutexes	*mutexes, int32_t count)
{
	int32_t	i;

	i = 0;
	if (pthread_mutex_init(&mutexes->voice, NULL))
			return (destroy_mutexes(mutexes, i, 1));
	if (pthread_mutex_init(&mutexes->id, NULL))
			return (destroy_mutexes(mutexes, i, 2));
	if (pthread_mutex_init(&mutexes->dead, NULL))
			return (destroy_mutexes(mutexes, i, 3));
	if (pthread_mutex_init(&mutexes->start, NULL))
			return (destroy_mutexes(mutexes, i, 4));
	while (i < count)
	{
		if (pthread_mutex_init(&mutexes->forks[i], NULL))
			return (destroy_mutexes(mutexes, i, 4));
		i++;
	}
	return (SUCCESS);
}

int32_t	destroy_mutexes(t_mutexes *mutexes, int32_t count, int32_t lvl)
{
	int	i;

	i = 0;
	if (lvl <= 1)
		pthread_mutex_destroy(&mutexes->voice);
	if (lvl <= 2)
		pthread_mutex_destroy(&mutexes->id);
	if (lvl <= 3)
		pthread_mutex_destroy(&mutexes->dead);
	if (lvl <= 4)
		pthread_mutex_destroy(&mutexes->start);
	while (i < count)
	{
		pthread_mutex_destroy(&mutexes->forks[i]);
		i++;	
	}
	return (ERROR);
}
