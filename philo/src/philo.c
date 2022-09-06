/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/06 15:10:11 by safoh        \___)=(___/                 */
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

int32_t	get_id(void *ptr)
{
	static int32_t	id;

	(void)ptr;
	return (++id);
}

int32_t	isdead(void *ptr)
{
	t_shared	*shared;

	shared = (t_shared *)ptr;
	return (shared->dead);
}

int32_t	canstart(void *ptr)
{
	t_shared	*shared;

	shared = (t_shared *)ptr;
	return (shared->start);
}

void	narrator(int64_t time, int32_t id, char *str)
{
	printf("%lld\t%d\t%s\n", time, id, str);
}

int32_t	eat(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	narrator(philo->time_diff, philo->id, EATING);
	return (time_in_ms());
}

int32_t update_done_philos(void *ptr)
{
	t_shared	*shared;

	shared = (t_shared *)ptr;
	shared->philos_done_eating++;
	return (0);
}

void	ft_usleep(int64_t millisec) //add ms
{
	int64_t time_stamp;

	time_stamp = time_in_ms();
	while (time_in_ms() - time_stamp < millisec)
	{
		usleep(500);
	}
}

int32_t	narrate_taken_fork(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_diff = time_diff_ms(philo->shared->start_time, time_in_ms());
	if (mutex_api(&philo->shared->mutexes[DEAD], isdead, philo->shared))
		return (DONE);
	narrator(philo->time_diff, philo->id, TOOK_FORK);
	return (SUCCESS);
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

	while (true)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&shared->mutexes[VOICE]);
			time_diff = time_diff_ms(shared->start_time, time_in_ms());
			narrator(time_diff, philo->id, TOOK_FORK);
			pthread_mutex_unlock(&shared->mutexes[VOICE]);
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&shared->mutexes[VOICE]);
			time_diff = time_diff_ms(shared->start_time, time_in_ms());
			narrator(time_diff, philo->id, TOOK_FORK);
			narrator(time_diff, philo->id, EATING);
			pthread_mutex_unlock(&shared->mutexes[VOICE]);
			ft_usleep(shared->cnf.time_eat);
			pthread_mutex_lock(&shared->mutexes[TIME]);
			philo->last_time_eaten = time_in_ms();
			pthread_mutex_unlock(&shared->mutexes[TIME]);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&shared->mutexes[VOICE]);
			time_diff = time_diff_ms(shared->start_time, time_in_ms());
			narrator(time_diff, philo->id, TOOK_FORK);
			pthread_mutex_unlock(&shared->mutexes[VOICE]);
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&shared->mutexes[VOICE]);
			time_diff = time_diff_ms(shared->start_time, time_in_ms());
			narrator(time_diff, philo->id, TOOK_FORK);
			narrator(time_diff, philo->id, EATING);
			pthread_mutex_unlock(&shared->mutexes[VOICE]);
			ft_usleep(shared->cnf.time_eat);
			pthread_mutex_lock(&shared->mutexes[TIME]);
			philo->last_time_eaten = time_in_ms();
			pthread_mutex_unlock(&shared->mutexes[TIME]);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}

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
		narrator(time_diff, philo->id, SLEEPING);
		pthread_mutex_unlock(&shared->mutexes[VOICE]);
		ft_usleep(shared->cnf.time_sleep);

		pthread_mutex_lock(&shared->mutexes[VOICE]);
		time_diff = time_diff_ms(shared->start_time, time_in_ms());
		narrator(time_diff, philo->id, THINKING);
		pthread_mutex_unlock(&shared->mutexes[VOICE]);
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

int32_t	cpy_philo_ptr(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->shared->philos[philo->id -1] = (t_philo *)ptr;
	return (SUCCESS);
}

int32_t	construct_philo(t_shared *shared, t_philo *philo)
{
	philo->id = mutex_api(&shared->mutexes[ID], get_id, NULL);
	if (philo->id == ERROR)
		return (ERROR);
	philo->last_time_eaten = 0;
	philo->servings = 0;
	philo->left_fork = &shared->mutexes[MUTEX + philo->id - 1];
	if (shared->cnf.nb_philo == 1)
		philo->right_fork = NULL;
	else
		philo->right_fork = &shared->mutexes[MUTEX + (philo->id % shared->cnf.nb_philo)];
	philo->shared = shared;
	mutex_api(&shared->mutexes[PTR], cpy_philo_ptr, philo);
	return (SUCCESS);
}

void	*philosopher(void *ptr)
{
	t_shared	*shared;
	t_philo		philo;
	int32_t		start;

	shared = (t_shared *)ptr;

	construct_philo(shared, &philo);
	if (pthread_mutex_lock(&shared->mutexes[BREED]))
		return (NULL);
	if (pthread_mutex_unlock(&shared->mutexes[BREED]))
		return (NULL);
	while (true)
	{
		
		if (mutex_api(&shared->mutexes[DEAD], isdead, shared))
			return (NULL);
		start = mutex_api(&shared->mutexes[START], canstart, shared);
		if (start == true)
			break ;
		if (start == ERROR)
			return (NULL);
	}
	start_feasting(shared, &philo);
	return (NULL);
}

int32_t 	get_last_time_eaten(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	return (philo->last_time_eaten);
}

int32_t	narrate_died(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_diff = time_diff_ms(philo->shared->start_time, time_in_ms());
	if (mutex_api(&philo->shared->mutexes[DEAD], isdead, philo->shared))
		return (DONE);
	mutex_api(&philo->shared->mutexes[DEAD], philo_has_died, ptr);
	return (SUCCESS);
}

int32_t	did_someone_die(void *ptr)
{
	t_philo		**philos;
	t_shared	*shared;
	int64_t		last_time_eaten;
	int64_t		i;

	i = 0;
	shared = ptr;
	pthread_mutex_lock(&shared->mutexes[PTR]);
	philos = shared->philos;
	pthread_mutex_unlock(&shared->mutexes[PTR]);
	while (philos[i] != NULL)
	{
		last_time_eaten = mutex_api(&shared->mutexes[TIME], get_last_time_eaten, philos[i]);
		if (time_in_ms() - last_time_eaten > shared->cnf.time_die)
			return (i);
		i++;
	}
	return (SUCCESS);
}

void	monitor_philosophers(t_shared *shared)
{
	int32_t	i;

	i = 0;
	(void)shared;
	ft_usleep(shared->cnf.time_die / 2);
	while (true)
	{
		i = did_someone_die(shared);
		if (i)
		{
			mutex_api(&shared->mutexes[VOICE], narrate_died, shared->philos[i]);
			return ;
		}
		if (mutex_api(&shared->mutexes[SERVINGS], check_servings, shared))
			return ;
	}
}

int32_t	allocate_memory(t_shared *shared, pthread_t **philosophers, int32_t n)
{
	shared->mutexes = malloc(n * sizeof(t_mutex));
	if (shared->mutexes == NULL)
		return (deallocate_memory(shared, philosophers));
	*philosophers = malloc(n * sizeof(pthread_t));
	if (!*philosophers)
		return (deallocate_memory(shared, philosophers));
	shared->philos = malloc((n + 1) * sizeof(t_philo *));
	if (shared->philos == NULL)
		return (deallocate_memory(shared, philosophers));
	ft_bzero(*philosophers, n * sizeof(pthread_t));
	ft_bzero(shared->mutexes, n * sizeof(t_mutex));
	ft_bzero(shared->philos, (n + 1) * sizeof(t_philo *));
	return (SUCCESS);
}

int32_t	philo(char **argv)
{
	t_shared	shared;
	pthread_t	*philosophers;

	philosophers = NULL;
	ft_bzero(&shared, sizeof(t_shared));
	if (get_config(&shared.cnf, argv) == ERROR)
		return (ERROR);
	if (allocate_memory(&shared, &philosophers, shared.cnf.nb_philo) == ERROR)
		return (ERROR);
	if (init_mutexes(&shared.mutexes, shared.cnf.nb_philo + MUTEX) == ERROR)
		return (deallocate_memory(&shared, &philosophers));
	if (breed_philosophers(&shared, &philosophers) == ERROR)
		return (clean_shared(&shared, &philosophers, shared.cnf.nb_philo));
	monitor_philosophers(&shared);
	return (clean_program(&shared, &philosophers, shared.cnf.nb_philo));
}
