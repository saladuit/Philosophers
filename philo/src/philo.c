/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/23 20:26:00 by safoh        \___)=(___/                 */
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
	philo->philo_id = 0;
	philo->count = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_sleep = ft_atoi(argv[3]);
	philo->eat_count = ft_atoi(argv[4]);
	if (argv[5])
		philo->philo_id = ft_atoi(argv[5]);
	else
		philo->philo_id = 0;
}

void	fill_philo_array(t_philo *philo_array, t_philo philo_settings)
{

void	init_philosophers(t_philo *philo_array, int argc, char **argv)
{
	t_philo philo_settings;

	construct_default_philo(&philo_settings, argc, argv);
	fill_philo_array(philo_array, &philo_settings);
}

void	philo(int argc, char **argv)
{
	int	size;
	pthread_t philosopher;
	t_philo	philo_array[MAX_PHILOSOPHERS];

	init_philosophers(philo_array, argc, argv);
	if (pthread_create(&philosopher, NULL, work, philo))
		printf("A thread error occured\n");
}
