/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/25 10:44:11 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	get_id(int16_t *shared_id, pthread_mutex_t id_lock) {
	int32_t		id;

	pthread_mutex_lock(&id_lock);
	(*shared_id)++;
	id = *shared_id;
	printf("I am philosopher: %d\n", id);
	pthread_mutex_unlock(&id_lock);
	return (id);
}

void *philosopher(void *p) {
	t_shared	*shared;
	int32_t		id;

	shared = (t_shared *)p;
	id = get_id(&shared->id, shared->id_lock);
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

void	collect_forks(pthread_mutex_t	*forks, int32_t count)
{
	int32_t	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	fill_settings(t_philo *settings, t_philo *standard, int32_t count)
{
	int32_t		i;

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
	t_philo standard;
	int32_t	count;

	count = ft_atoi(argv[1]);
	construct_settings(&standard, argv);
	fill_settings(settings, &standard, count);
	return (count);
}

void	init(t_shared *shared, char **argv)
{
	shared->count = init_philosophers(shared->settings, argv);
	collect_forks(shared->forks, shared->count);
	pthread_mutex_init(&shared->id_lock, NULL);
}

pthread_t	make_thread(void *(*routine)(void *), void *shared)
{
	pthread_t	thread;

	thread = NULL;
	if (pthread_create(&thread, NULL, routine, shared))
		exit(-1);
	return (thread);
}

void	join_thread(pthread_t *thread)
{
	if (pthread_join(*thread, NULL))
		exit(-1);
}

void	start_eating_spaghetti(t_shared *shared)
{
	int32_t	i;

	i = 0;
	while (i < shared->count)
	{
		shared->philosophers[i] = make_thread(philosopher, shared);
		join_thread(&shared->philosophers[i]);
		i++;
	}
}

void	philo(char **argv)
{
	t_shared	shared;

	init(&shared, argv);
	start_eating_spaghetti(&shared);
}
