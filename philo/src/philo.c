/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/25 16:16:12 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	ft_check_shared_bool(pthread_mutex_t *mutex, bool *input)
{
	bool result;

	result = false;
	pthread_mutex_lock(mutex);
	result = *input;
	pthread_mutex_unlock(mutex);
	if (result == true)
		return (true);
	return (false);
}

void	philosopher_died(pthread_mutex_t *dead_lock, bool *dead)
{
	pthread_mutex_lock(dead_lock);
	*dead = true;
	pthread_mutex_unlock(dead_lock);
}

void	take_fork(pthread_mutex_t *fork, time_t time, int32_t id)
{
	pthread_mutex_lock(fork);
	printf("%ld %d has taken a fork\n", time, id);
}

void	put_down_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

int16_t	get_id(pthread_mutex_t *id_lock, int32_t *shared_id)
{
	int16_t	id;

	pthread_mutex_lock(id_lock);
	(*shared_id)++;
	id = *shared_id;
	printf("I am philosopher: %d\n", id);
	pthread_mutex_unlock(id_lock);
	return (id);
}

void	*philosopher(void *p) {
	t_shared	*shared;
	int16_t		id;

	shared = (t_shared *)p;
	while (!shared->start)
		continue ;
	id = get_id(shared->mutexes.id_lock, &shared->id);
	philosopher_died(shared->mutexes.dead_lock, &shared->dead);
	return (NULL);
}

void	construct_settings(t_philo *settings, char **argv)
{
	settings->time_die = ft_atoi(argv[2]);
	settings->time_eat = ft_atoi(argv[3]);
	settings->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		settings->eat_count = ft_atoi(argv[5]);
	else
		settings->eat_count = -1;
}

void	fill_settings(t_philo *settings, t_philo *standard, int32_t count)
{
	int32_t	i;

	i = 0;
	while (i < count)
	{
		*settings = *standard;
		settings->left_fork = i;
		settings->right_fork = (i + 1) % count;
		i++;
		settings++;
	}
}

int32_t	init_philosophers(t_philo *settings, char **argv)
{
	t_philo	standard;
	int32_t	count;

	count = ft_atoi(argv[1]);
	construct_settings(&standard, argv);
	fill_settings(settings, &standard, count);
	return (count);
}

int32_t	destroy_mutexes(t_mutexes *mutexes, int32_t count)
{
	int	i;

	i = 0;
	if (mutexes->voice)
		pthread_mutex_destroy(mutexes->voice);
	if (mutexes->id_lock)
		pthread_mutex_destroy(mutexes->id_lock);
	if (mutexes->dead_lock)
		pthread_mutex_destroy(mutexes->dead_lock);
	while (i < count)
	{
		pthread_mutex_destroy(mutexes->forks[i]);
		i++;	
	}
	return (ERROR);
}

int32_t	collect_forks(t_mutexes	*mutexes, int32_t count)
{
	int32_t	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(mutexes->forks[i], NULL))
			return (destroy_mutexes(mutexes, i));
		i++;
	}
	return (SUCCESS);
}

int32_t	clean_table(pthread_t *philosophers, int32_t count)
{
	int	i;

	i = 0;
	while (i <count)
	{
		pthread_detach(philosophers[i]);
		i++;	
	}
	return (ERROR);
}

void	init(t_shared *shared, char **argv)
{
	shared->count = init_philosophers(shared->settings, argv);
	pthread_mutex_init(shared->mutexes.voice, NULL);
	pthread_mutex_init(shared->mutexes.id_lock, NULL);
	pthread_mutex_init(shared->mutexes.dead_lock, NULL);
	collect_forks(&shared->mutexes, shared->count);
}

int32_t	make_thread(void *(*routine)(void *), void *shared, pthread_t *thread)
{

	*thread = NULL;
	if (pthread_create(thread, NULL, routine, shared))
		return (ERROR);
	return (SUCCESS);
}

int32_t	join_thread(pthread_t *thread)
{
	if (pthread_join(*thread, NULL))
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

int32_t	start_diner(t_shared *shared)
{
	int32_t	i;

	i = 0;
	shared->start = true;
	while (i < shared->count)
	{
		join_thread(&shared->philosophers[i]);
		i++;
	}
	return (SUCCESS);
}

void	philo(char **argv)
{
	t_shared	shared;

	init(&shared, argv);
	if (breed_philosophers(&shared) == ERROR)
		return ;
	if (start_diner(&shared) == ERROR)
		return ;
}
