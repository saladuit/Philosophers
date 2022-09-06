/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/06 09:54:56 by safoh        \___)=(___/                 */
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

void	ft_usleep(int64_t time)
{
	int64_t time_stamp;

	time_stamp = time_in_ms();
	while (time_in_ms() - time_stamp < time)
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

int32_t	narrate_is_eating(void *ptr)
{
	int64_t timestamp;
	t_philo	*philo;

	philo = (t_philo *)ptr;

	timestamp = time_in_ms();
	philo->time_diff = time_diff_ms(philo->shared->start_time, timestamp);
	if (mutex_api(&philo->shared->mutexes[DEAD], isdead, philo->shared))
		return (DONE);
	narrator(philo->time_diff, philo->id, EATING);
	philo->last_time_eaten = timestamp;
	ft_usleep(philo->shared->cnf.time_eat);
	return (SUCCESS);
}

int32_t	narrate_is_thinking(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_diff = time_diff_ms(philo->shared->start_time, time_in_ms());
	if (mutex_api(&philo->shared->mutexes[DEAD], isdead, philo->shared))
		return (DONE);
	narrator(philo->time_diff, philo->id, THINKING);
	return (SUCCESS);
}

int32_t	narrate_is_sleeping(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_diff = time_diff_ms(philo->shared->start_time, time_in_ms());
	if (mutex_api(&philo->shared->mutexes[DEAD], isdead, philo->shared))
		return (DONE);
	narrator(philo->time_diff, philo->id, SLEEPING);
	ft_usleep(philo->shared->cnf.time_sleep);
	return (SUCCESS);
}

int32_t	take_left_fork_second(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (mutex_api(&philo->shared->mutexes[VOICE], narrate_taken_fork, ptr))
		return (DONE);
	if (mutex_api(&philo->shared->mutexes[VOICE], narrate_is_eating, ptr))
		return (DONE);
	return (SUCCESS);
}

int32_t	take_right_fork_first(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (mutex_api(&philo->shared->mutexes[VOICE], narrate_taken_fork, ptr))
		return (DONE);
	if (mutex_api(philo->left_fork, take_left_fork_second, ptr))
		return (DONE);
	return (SUCCESS);
}

int32_t	take_right_fork_second(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (mutex_api(&philo->shared->mutexes[VOICE], narrate_taken_fork, ptr))
		return (DONE);
	if (mutex_api(&philo->shared->mutexes[VOICE], narrate_is_eating, ptr))
		return (DONE);
	return (SUCCESS);
}

int32_t	take_left_fork_first(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_diff = time_diff_ms(philo->shared->start_time, time_in_ms());
	if (mutex_api(&philo->shared->mutexes[VOICE], narrate_taken_fork, ptr))
		return (DONE);
	if (mutex_api(philo->right_fork, take_right_fork_second, ptr))
		return (DONE);
	return (SUCCESS);
}

void	start_feasting(t_shared *shared, t_philo *philo)
{
	philo->last_time_eaten = time_in_ms();
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			if (mutex_api(philo->left_fork, take_left_fork_first, philo))
				return ;
		}
		else
		{
			if (mutex_api(philo->right_fork, take_right_fork_first, philo))
				return ;
		}
		if (mutex_api(&shared->mutexes[VOICE], narrate_is_sleeping, philo))
			return ;
		if (mutex_api(&shared->mutexes[VOICE], narrate_is_thinking, philo))
			return ;
		philo->servings++;
		if (philo->servings == shared->cnf.minimum_servings)
		{
			mutex_api(&shared->mutexes[SHARED], update_done_philos, shared);
			return ;
		}
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
	philo->id = mutex_api(&shared->mutexes[SHARED], get_id, NULL);
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
	mutex_api(&shared->mutexes[SHARED], cpy_philo_ptr, philo);
	return (SUCCESS);
}

void	*philosopher(void *ptr)
{
	t_shared	*shared;
	t_philo		philo;
	int32_t		start;

	shared = (t_shared *)ptr;

	construct_philo(shared, &philo);
	while (true)
	{
		if (mutex_api(&shared->mutexes[START], isdead, shared))
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
	return (*((int64_t *)ptr));
}

int32_t	check_philosophers(void *ptr)
{
	t_shared	*shared;
	t_philo	**philos;
	int64_t		i;

	shared = ptr;
	philos = shared->philos;
	i = 0;
	while (philos[i] != NULL)
	{
		if (time_in_ms() - mutex_api(&shared->mutexes[DEAD], get_last_time_eaten, &philos[i]->last_time_eaten) > shared->cnf.time_die)
		{
			mutex_api(&shared->mutexes[VOICE], narrate_died, philos[i]);
			return (SUCCESS);

		}
		i++;
	}
	return (SUCCESS);
}

void	monitor_philosophers(t_shared *shared)
{
	int32_t	i;

	i = 0;
	while (true)
	{
		if (mutex_api(&shared->mutexes[SHARED], check_philosophers, shared))
			return ;
		if (mutex_api(&shared->mutexes[SHARED], check_servings, shared))
			return ;
	}
}

int32_t	philo(char **argv)
{
	t_shared	shared;
	pthread_t	*philosophers;

	ft_bzero(&shared, sizeof(t_shared));
	if (get_config(&shared.cnf, argv) == ERROR)
		return (ERROR);
	if (init_mutexes(&shared.mutexes, shared.cnf.nb_philo + MUTEX) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX));
	philosophers = NULL;
	shared.philos = malloc((shared.cnf.nb_philo + 1) * sizeof(t_philo *));
	ft_bzero(shared.philos, (shared.cnf.nb_philo + 1) * sizeof(t_philo *));
	if (shared.philos == NULL)
		return (ERROR);
	if (breed_philosophers(&shared, &philosophers) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX));
	monitor_philosophers(&shared);
	if (clean_philosophers(philosophers, shared.cnf.nb_philo) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX));
	destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX);
	return (SUCCESS);
}
