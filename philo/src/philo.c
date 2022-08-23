/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/23 21:42:58 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void *work(void * p) {
	if (p == NULL)
		return (NULL);
	return (NULL);
}

void	construct_default_philo(t_philo *philo, int argc, char **argv)
{
	philo->id = 0;
	philo->count = ft_atoi(argv[1]); //exit if count is bigger than MAX
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->eat_count = ft_atoi(argv[5]);
	else
		philo->eat_count = 0;
}

void	fill_forks(pthread_mutex_t	*forks, int32_t count)
{
	int32_t	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	fill_philo_array(t_philo *philo_array, t_philo *philo_settings)
{
	pthread_mutex_t	forks[MAX_PHILOSOPHERS];

	fill_forks(forks, philo_settings->count);
	while (philo_settings->id < philo_settings->count)
	{
		*philo_array = *philo_settings;
		philo_array->left_fork = *(forks + philo_settings->id);
		philo_array->right_fork = *(forks + (philo_settings->id + 1) % (philo_settings->count));
		philo_settings->id++;
		philo_array++;
	}
	memset((void *)&*philo_array, 0, sizeof(t_philo));
}

void	init_philosophers(t_philo *philo_array, int argc, char **argv)
{
	t_philo philo_settings;

	construct_default_philo(&philo_settings, argc, argv);
	fill_philo_array(philo_array, &philo_settings);
}

void	philo(int argc, char **argv)
{
	pthread_t philosopher;
	t_philo	philo_array[MAX_PHILOSOPHERS];

	init_philosophers(philo_array, argc, argv);
	if (pthread_create(&philosopher, NULL, work, philo))
		printf("A thread error occured\n");
}
