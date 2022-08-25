/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/25 17:57:57 by safoh        \___)=(___/                 */
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

void	ft_switch_shared_bool(pthread_mutex_t *mutex, bool *input)
{
	pthread_mutex_lock(mutex);
	if (*input == true)
		*input = false;
	else
		*input = true;
	pthread_mutex_unlock(mutex);
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
	while (!ft_check_shared_bool(&shared->mutexes.start, &shared->start))
		continue ;
	id = get_id(&shared->mutexes.id, &shared->id);
	ft_switch_shared_bool(&shared->mutexes.dead, &shared->dead);
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

int32_t	clean_table(pthread_t *philosophers, int32_t count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_detach(philosophers[i]);
		i++;	
	}
	return (ERROR);
}

int32_t	init(t_shared *shared, char **argv)
{
	shared->count = init_philosophers(shared->settings, argv);
	if (init_mutexes(&shared->mutexes, shared->count))
		return (ERROR);
	return (SUCCESS);
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
	ft_switch_shared_bool(&shared->mutexes.start, &shared->start);
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
	destroy_mutexes();
}
