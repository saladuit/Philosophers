/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/04 12:08:26 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>


int64_t	time_in_ms(void) {
    t_timeval tv;

    gettimeofday(&tv,NULL);
    return ((tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

int64_t	time_diff_ms(int64_t start, int64_t end)
{
    return ((end - start) * 1000) + ((end - start) / 1000);
}

int32_t	get_id(void *ptr)
{
	int32_t	id;

	id = ((t_config *)ptr)->nb_philo;
	((t_config *)ptr)->nb_philo--;
	return (id);
}

int32_t	isdead(void *ptr)
{
	return (((t_shared *)ptr)->dead);
}

int32_t	canstart(void *ptr)
{
	return (((t_shared *)ptr)->start);
}

void	narrator(int64_t time, int32_t id, char *str)
{
	printf("%lld\t%d\t%s\n", time, id, str);
}

int32_t	eat(void *ptr)
{
	narrator(((t_philo *)ptr)->time_diff, ((t_philo *)ptr)->id, EATING);
	return (time_in_ms());
}

int32_t died(void *ptr)
{
	narrator(time_in_ms(), ((t_philo *)ptr)->id, DIED);
	return (0);
}

void	start_feasting(t_shared *shared, t_philo *philo)
{
	while (1)
	{
		philo->time_diff = time_diff_ms(shared->start_time, time_in_ms());
		philo->last_time_eaten = mutex_api(&shared->mutexes[VOICE], eat, philo);
		if (philo->last_time_eaten == ERROR)
			return ;
		philo->servings++;
		usleep(shared->cnf.time_eat * 1000);
		if (philo->servings == shared->cnf.minimum_servings)
			return ;
	}
}

int32_t	check_all_eat_count(void *ptr)
{
	if (((t_shared *)ptr)->philos_done_eating == ((t_shared *)ptr)->cnf.nb_philo)
		return (DONE);
	return (SUCCESS);
}

int32_t	construct_philo(t_shared *shared, t_philo *philo)
{
	philo->id = mutex_api(&shared->mutexes[SHARED], get_id, &shared->cnf);
	if (philo->id == ERROR)
		return (ERROR);
	philo->last_time_eaten = 0;
	philo->servings = 0;
	philo->left_fork = &shared->mutexes[philo->id - 1];
	if (shared->cnf.nb_philo > 1)
		philo->right_fork = &shared->mutexes[philo->id % shared->cnf.nb_philo];
	else
		philo->right_fork = NULL;
	return (SUCCESS);
}

void	*philosopher(void *ptr)
{
	t_shared	*shared;
	t_philo		philo;
	int32_t		start;

	shared = (t_shared *)ptr;

	while (1)
	{
		if (mutex_api(&shared->mutexes[START], isdead, shared))
			return (NULL);
		start = mutex_api(&shared->mutexes[START], canstart, shared);
		if (start == true)
			break ;
		if (start == ERROR)
			return (NULL);
	}
	construct_philo(shared, &philo);
	start_feasting(shared, &philo);
	return (NULL);
}

void	monitor_philosophers(t_shared *shared)
{
	int32_t	i;

	i = 0;
	while (1)
	{
		if (mutex_api(&shared->mutexes[SHARED], isdead, shared))
			if (mutex_api(&shared->mutexes[VOICE], died, shared))
				return ;
		if (mutex_api(&shared->mutexes[SHARED], check_all_eat_count, shared) == 1)
			return ;
	}
}

int32_t	philo(char **argv)
{
	t_shared	shared;
	pthread_t	philosophers[MAX_PHILOSOPHERS];

	ft_bzero(&shared, sizeof(t_shared));
	if (get_config(&shared.cnf, argv) == ERROR)
		return (ERROR);
	if (init_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX))
		return (destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX));
	if (breed_philosophers(&shared, philosophers) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX));
	monitor_philosophers(&shared);
	if (clean_philosophers(philosophers, shared.cnf.nb_philo) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX));
	destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX);
	return (SUCCESS);
}
