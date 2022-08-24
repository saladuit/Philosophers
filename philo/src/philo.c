/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/24 19:13:06 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void *philo_routine(void *p) {
	t_shared	*shared;

	shared = (t_shared *)p;
	if (p == NULL)
		return (NULL);
	return (NULL);
}

void	construct_default_philo(t_philo *philo, char **argv)
{
	philo->id = 0;
	philo->count = ft_atoi(argv[1]); //exit if count is bigger than MAX_PHIL
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->eat_count = ft_atoi(argv[5]);
	else
		philo->eat_count = -1;
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
    pthread_t thread;

    if (pthread_create(&thread, NULL, routine, shared))
        exit(-1);
    return (thread);
}

void	fill_philo_array(t_philo *philo_array, t_philo *philo_settings)
{

	while (philo_settings->id < philo_settings->count)
	{
		*philo_array = *philo_settings;
		philo_array->left_fork = philo_settings->id;
		philo_array->right_fork = (philo_settings->id + 1) % philo_settings->count;
		philo_settings->id++;
		philo_array++;
	}
	memset((void *)&*philo_array, 0, sizeof(t_philo)); //remove?
}

int32_t	init_philosophers(t_philo *philo_array, char **argv)
{
	t_philo philo_settings;

	construct_default_philo(&philo_settings, argv);
	fill_philo_array(philo_array, &philo_settings);
	return (philo_settings.count);
}

void	init(t_shared *shared, char **argv)
{
	collect_forks(shared->forks, init_philosophers(shared->philo_array, argv));
}
void	start_eating_spaghetti(t_shared *shared)
{

}
void	philo(char **argv)
{
	t_shared	shared;

	init(&shared, argv);
	start_eating_spaghetti(&shared);
}
