/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   thread.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:08:07 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/30 14:26:08 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	join_thread(pthread_t *thread)
{
	if (pthread_join(*thread, NULL))
		return (ERROR);
	return (SUCCESS);
}

int32_t	clean_table(pthread_t *philosophers, int32_t count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_detach(philosophers[i]))
			return (ERROR);
		i++;	
	}
	return (SUCCES);
}

int32_t	start_diner(t_shared *shared)
{
	int32_t	i;

	i = 0;
	ft_switch_shared_bool(&shared->mutexes.start, &shared->start);
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

	*thread = NULL;
	if (pthread_create(thread, NULL, routine, shared))
		return (ERROR);
	return (SUCCESS);
}

int32_t	breed_philosophers(t_shared *shared)
{
	int32_t	i;

	i = 0;
	while (i < shared->count)
	{
		if (make_thread(philosopher, shared, &shared->philosophers[i]) == ERROR)
			return (clean_table(shared->philosophers, i));
		i++;
	}
	return (SUCCESS);
}
