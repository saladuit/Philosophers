/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   routine.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/07 17:12:21 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/07 19:36:12 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	start_feasting(t_shared *shared, t_philo *philo)
{
	int64_t	time_diff;
	bool 	done;

	done = false;
	while (true)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&shared->mutexes[VOICE]);
			time_diff = time_diff_ms(shared->start_time, time_in_ms());
			if (!done)
				done = narrator(time_diff, philo->id, TOOK_FORK, shared);
			pthread_mutex_unlock(&shared->mutexes[VOICE]);
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&shared->mutexes[VOICE]);
			time_diff = time_diff_ms(shared->start_time, time_in_ms());
			if (!done)
				done = narrator(time_diff, philo->id, TOOK_FORK, shared);
			if (!done)
				done = narrator(time_diff, philo->id, EATING, shared);
			pthread_mutex_unlock(&shared->mutexes[VOICE]);
			pthread_mutex_lock(&shared->mutexes[TIME]);
			philo->last_time_eaten = time_in_ms();
			pthread_mutex_unlock(&shared->mutexes[TIME]);
			ft_mssleep(shared->cnf.time_eat, shared);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&shared->mutexes[VOICE]);
			time_diff = time_diff_ms(shared->start_time, time_in_ms());
			if (!done)
				done = narrator(time_diff, philo->id, TOOK_FORK, shared);
			pthread_mutex_unlock(&shared->mutexes[VOICE]);
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&shared->mutexes[VOICE]);
			time_diff = time_diff_ms(shared->start_time, time_in_ms());
			if (!done)
				done = narrator(time_diff, philo->id, TOOK_FORK, shared);
			if (!done)
				done = narrator(time_diff, philo->id, EATING, shared);
			pthread_mutex_unlock(&shared->mutexes[VOICE]);
			pthread_mutex_lock(&shared->mutexes[TIME]);
			philo->last_time_eaten = time_in_ms();
			pthread_mutex_unlock(&shared->mutexes[TIME]);
			ft_mssleep(shared->cnf.time_eat, shared);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		philo->servings++;
		if (done)
			return ;
		if (philo->servings == shared->cnf.minimum_servings)
		{
			philo->servings++;
			if (philo->servings == shared->cnf.minimum_servings)
			{
				pthread_mutex_lock(&shared->mutexes[SERVINGS]);
				shared->philos_done_eating++;
				pthread_mutex_unlock(&shared->mutexes[SERVINGS]);
				return ;
			}
			pthread_mutex_lock(&shared->mutexes[SERVINGS]);
			shared->philos_done_eating++;
			pthread_mutex_unlock(&shared->mutexes[SERVINGS]);
			return ;
		}

		pthread_mutex_lock(&shared->mutexes[VOICE]);
		time_diff = time_diff_ms(shared->start_time, time_in_ms());
		if (!done)
			done = narrator(time_diff, philo->id, SLEEPING, shared);
		pthread_mutex_unlock(&shared->mutexes[VOICE]);
		ft_mssleep(shared->cnf.time_sleep, shared);

		if (done)
			return ;
		pthread_mutex_lock(&shared->mutexes[VOICE]);
		time_diff = time_diff_ms(shared->start_time, time_in_ms());
		if (!done)
			done = narrator(time_diff, philo->id, THINKING, shared);
		pthread_mutex_unlock(&shared->mutexes[VOICE]);
		if (done)
			return ;
	}
}

void	*philosopher(void *ptr)
{
	t_philo		*philo;
	t_shared	*shared;
	int32_t		start;

	philo = (t_philo *)ptr;
	shared = philo->shared;
	if (pthread_mutex_lock(&shared->mutexes[BREED]))
		return (NULL);
	if (pthread_mutex_unlock(&shared->mutexes[BREED]))
		return (NULL);
	while (true)
	{

		if (mutex_api(&shared->mutexes[MUTERROR], sharedbool, &shared->error))
			return (NULL);
		start = mutex_api(&shared->mutexes[START], sharedbool, &shared->start);
		if (start == true)
			break ;
		if (start == ERROR)
			return (NULL);
	}
	start_feasting(shared, philo);
	return (NULL);
}
