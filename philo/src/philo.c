/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/24 19:39:40 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void *philosopher(void *p) {
	t_shared	*shared;

	shared = (t_shared *)p;
	if (p == NULL)
		return (NULL);
	return (NULL);
}

void	construct_settings(t_philo *settings, char **argv)
{
	settings->id = 0;
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

pthread_t make_thread(void *(*routine)(void *), void *shared)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, routine, shared))
		exit(-1);
	return (thread);
}

void	fill_philo_array(t_philo *array, t_philo *settings, int32_t count)
{

	while (settings->id < count)
	{
		*array = *settings;
		array->left_fork = settings->id;
		array->right_fork = (settings->id + 1) % count;
		settings->id++;
		array++;
	}
//	memset((void *)&*philo_array, 0, sizeof(t_philo)); //remove?
}

int32_t	init_philosophers(t_philo *array, char **argv)
{
	t_philo settings;
	int32_t	count;

	count = ft_atoi(argv[1]);
	construct_settings(&settings, argv);
	fill_philo_array(array, &settings, count);
	return (count);
}

void	init(t_shared *shared, char **argv)
{
	shared->count = init_philosophers(shared->array, argv);
	collect_forks(shared->forks, shared->count);
}

void	start_eating_spaghetti(t_shared *shared)
{
	int32_t	i;

	i = 0;
	while (i < shared->count)
	{
		shared->philosophers[i] = make_thread(philosopher, shared);
		i++;
	}
}

void	philo(char **argv)
{
	t_shared	shared;

	init(&shared, argv);
	start_eating_spaghetti(&shared);
}
