/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   thread.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:08:07 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/31 18:48:29 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_switch_bool(bool *input)
{
	if (*input == true)
		*input = false;
	else
		*input = true;
}

int32_t	breeding_done(t_shared *shared)
{
	ft_switch_bool(&shared->start);
	return (0);
}

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
	return (SUCCESS);
}

int32_t	start_diner(t_shared *shared)
{
	int32_t	i;

	i = 0;
	mutex_api(&shared->mutexes.start, NULL, NULL);
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

	*thread = 0;
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
