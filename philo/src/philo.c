/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/05 10:30:08 by safoh        \___)=(___/                 */
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

int32_t update_done_philos(void *ptr)
{
	((t_shared *)ptr)->philos_done_eating++;
	return (0);
}

void	ft_usleep(int64_t time)
{
	int64_t current_time;

	current_time = time_in_ms();
	while (time_in_ms() - current_time < time)
	{
		usleep(100);
	}
}

int32_t	narrate_taken_fork(void *ptr)
{
		((t_philo *)ptr)->time_diff = time_diff_ms(((t_philo *)ptr)->shared->start_time, time_in_ms());
		narrator(((t_philo *)ptr)->time_diff, ((t_philo *)ptr)->id, TOOK_FORK);
		return (SUCCESS);
}

int32_t	narrate_is_eating(void *ptr)
{
		((t_philo *)ptr)->time_diff = time_diff_ms(((t_philo *)ptr)->shared->start_time, time_in_ms());
		narrator(((t_philo *)ptr)->time_diff, ((t_philo *)ptr)->id, EATING);
		ft_usleep(((t_philo *)ptr)->shared->cnf.time_eat);
		return (SUCCESS);
}

int32_t	narrate_is_thinking(void *ptr)
{
		((t_philo *)ptr)->time_diff = time_diff_ms(((t_philo *)ptr)->shared->start_time, time_in_ms());
		narrator(((t_philo *)ptr)->time_diff, ((t_philo *)ptr)->id, THINKING);
		return (SUCCESS);
}

int32_t	narrate_is_sleeping(void *ptr)
{
		((t_philo *)ptr)->time_diff = time_diff_ms(((t_philo *)ptr)->shared->start_time, time_in_ms());
		narrator(((t_philo *)ptr)->time_diff, ((t_philo *)ptr)->id, SLEEPING);
		ft_usleep(((t_philo *)ptr)->shared->cnf.time_sleep);
		return (SUCCESS);
}

int32_t	take_left_fork_second(void *ptr)
{
		mutex_api(&((t_philo *)ptr)->shared->mutexes[VOICE], narrate_taken_fork, ptr);
		mutex_api(&((t_philo *)ptr)->shared->mutexes[VOICE], narrate_is_eating, ptr);
		return (SUCCESS);
}

int32_t	take_right_fork_first(void *ptr)
{
		mutex_api(&((t_philo *)ptr)->shared->mutexes[VOICE], narrate_taken_fork, ptr);
		if (mutex_api(((t_philo *)ptr)->left_fork, take_left_fork_second, ptr) == ERROR)
			return (ERROR);
		return (SUCCESS);
}

int32_t	take_right_fork_second(void *ptr)
{
		mutex_api(&((t_philo *)ptr)->shared->mutexes[VOICE], narrate_taken_fork, ptr);
		mutex_api(&((t_philo *)ptr)->shared->mutexes[VOICE], narrate_is_eating, ptr);
		return (SUCCESS);
}

int32_t	take_left_fork_first(void *ptr)
{
		((t_philo *)ptr)->time_diff = time_diff_ms(((t_philo *)ptr)->shared->start_time, time_in_ms());
		mutex_api(&((t_philo *)ptr)->shared->mutexes[VOICE], narrate_taken_fork, ptr);
		if (mutex_api(((t_philo *)ptr)->right_fork, take_right_fork_second, ptr) == ERROR)
			return (ERROR);
		return (SUCCESS);
}

void	start_feasting(t_shared *shared, t_philo *philo)
{
	while (1)
	{
		if (philo->id % 2 == 0)
			mutex_api(philo->left_fork, take_left_fork_first, philo);
		else
			mutex_api(philo->right_fork, take_right_fork_first, philo);
		mutex_api(&shared->mutexes[VOICE], narrate_is_sleeping, philo);
		mutex_api(&shared->mutexes[VOICE], narrate_is_thinking, philo);
		if (philo->last_time_eaten == ERROR)
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
	if (((t_shared *)ptr)->philos_done_eating == ((t_shared *)ptr)->cnf.nb_philo)
		return (DONE);
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
	return (SUCCESS);
}

void	*philosopher(void *ptr)
{
	t_shared	*shared;
	t_philo		philo;
	int32_t		start;

	shared = (t_shared *)ptr;

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
	construct_philo(shared, &philo);
	start_feasting(shared, &philo);
	return (NULL);
}

void	monitor_philosophers(t_shared *shared)
{
	int32_t	i;

	i = 0;
	while (true)
	{
		if (mutex_api(&shared->mutexes[SHARED], isdead, shared))
			if (mutex_api(&shared->mutexes[VOICE], died, shared))
				return ;
		if (mutex_api(&shared->mutexes[SHARED], check_servings, shared) == DONE)
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
	if (breed_philosophers(&shared, &philosophers) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX));
	monitor_philosophers(&shared);
	if (clean_philosophers(philosophers, shared.cnf.nb_philo) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX));
	destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX);
	return (SUCCESS);
}
