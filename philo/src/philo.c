/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/07 11:45:01 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int64_t	time_in_ms(void) {
	t_timeval	tv;

	gettimeofday(&tv,NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int64_t	time_diff_ms(int64_t start, int64_t end)
{
	return (end - start);
}

int32_t	isdead(void *ptr)
{
	t_shared	*shared;

	shared = (t_shared *)ptr;
	return (shared->dead);
}

int32_t	checkerror(void *ptr)
{
	t_shared	*shared;

	shared = (t_shared *)ptr;
	return (shared->error);
}

int32_t	canstart(void *ptr)
{
	t_shared	*shared;

	shared = (t_shared *)ptr;
	return (shared->start);
}

bool	narrator(int64_t time, int32_t id, char *str, t_shared *shared)
{
	if (mutex_api(&shared->mutexes[DEAD], isdead, shared) == true)
		return (true);
	printf("%lld\t%d\t%s\n", time, id, str);
	return (false);
}

void	ft_mssleep(int64_t millisec, t_shared *shared)
{
	int64_t time_stamp;

	time_stamp = time_in_ms();
	while (time_in_ms() - time_stamp < millisec)
	{
		if (mutex_api(&shared->mutexes[DEAD], isdead, shared))
			return ;
		usleep(300);
	}
}

int32_t philo_has_died(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->shared->dead = true;
	return (SUCCESS);
}

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
		if (done)
			return ;
		philo->servings++;
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
		philo->servings++;
		if (philo->servings == shared->cnf.minimum_servings)
		{
			pthread_mutex_lock(&shared->mutexes[SERVINGS]);
			shared->philos_done_eating++;
			pthread_mutex_unlock(&shared->mutexes[SERVINGS]);
			return ;
		}
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

int32_t	check_servings(void *ptr)
{
	t_shared	*shared;

	shared = (t_shared *)ptr;
	if (shared->philos_done_eating == shared->cnf.nb_philo)
		return (DONE);
	return (SUCCESS);
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

		if (mutex_api(&shared->mutexes[MUTERROR], checkerror, shared))
			return (NULL);
		start = mutex_api(&shared->mutexes[START], canstart, shared);
		if (start == true)
			break ;
		if (start == ERROR)
			return (NULL);
	}
	start_feasting(shared, philo);
	return (NULL);
}

int32_t	narrate_died(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_diff = time_diff_ms(philo->shared->start_time, time_in_ms());
	if (mutex_api(&philo->shared->mutexes[DEAD], isdead, philo->shared))
		return (DONE);
	narrator(philo->time_diff, philo->id, DIED, philo->shared);
	mutex_api(&philo->shared->mutexes[DEAD], philo_has_died, ptr);
	return (SUCCESS);
}

int32_t	did_someone_die(void *ptr)
{
	t_philo		*philos;
	t_shared	*shared;
	int64_t		last_time_eaten;
	int64_t		i;

	i = 0;
	shared = ptr;
	philos = shared->philos;
	while (i < shared->cnf.nb_philo)
	{
		pthread_mutex_lock(&shared->mutexes[TIME]);
		last_time_eaten = philos[i].last_time_eaten;
		pthread_mutex_unlock(&shared->mutexes[TIME]);
		if (time_in_ms() - last_time_eaten > shared->cnf.time_die)
		{
			mutex_api(&shared->mutexes[VOICE], narrate_died, &shared->philos[i]);
			return (DONE);
		}
		i++;
	}
	return (SUCCESS);
}

void	monitor_philosophers(t_shared *shared)
{
	while (true)
	{
		if (did_someone_die(shared) == DONE)
			return ;
		if (mutex_api(&shared->mutexes[SERVINGS], check_servings, shared))
			return ;
	}
}

int32_t	philo(char **argv)
{
	t_shared	shared;
	pthread_t	*philosophers;

	philosophers = NULL;
	ft_bzero(&shared, sizeof(t_shared));
	if (get_config(&shared.cnf, argv) == ERROR)
		return (ERROR);
	if (shared.cnf.nb_philo == 1)
	{
		printf("%d\t%d\t%s\n", 0, 1, DIED);
		return (DONE);
	}
	if (allocate_memory(&shared, &philosophers, shared.cnf.nb_philo) == ERROR)
		return (ERROR);
	if (init_mutexes(&shared.mutexes, shared.cnf.nb_philo + MUTEX) == ERROR)
		return (deallocate_memory(&shared, &philosophers));
	init_philos(&shared, shared.cnf.nb_philo);
	if (breed_philosophers(&shared, &philosophers) == ERROR)
		return (clean_shared(&shared, &philosophers, shared.cnf.nb_philo));
	monitor_philosophers(&shared);
	return (clean_program(&shared, &philosophers, shared.cnf.nb_philo));
}
