/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   init.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:03:41 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/10/30 16:09:26 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	construct_philo(t_shared *shared, t_philo *philo, int32_t i)
{
	philo->done = false;
	philo->id = i + 1;
	philo->last_time_eaten = time_in_ms();
	philo->servings = 0;
	philo->left_fork = &shared->mutexes[MUTEX + i];
	if (shared->cnf.nb_philo == 1)
		philo->right_fork = NULL;
	else
		philo->right_fork = &shared->mutexes[MUTEX + \
							(philo->id % shared->cnf.nb_philo)];
	philo->shared = shared;
}

void	init_philos(t_shared *shared, int32_t count)
{
	int32_t	i;

	i = 0;
	while (i < count)
	{
		construct_philo(shared, &shared->philos[i], i);
		i++;
	}
}

int32_t	init_mutexes(t_mutex **mutexes, int32_t count)
{
	int32_t	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&(*mutexes)[i], NULL))
			return (clean_mutexes(mutexes, i));
		i++;
	}
	return (SUCCESS);
}

int32_t	allocate_memory(t_shared *shared, pthread_t **philosophers, int32_t n)
{
	shared->mutexes = malloc((n + MUTEX) * sizeof(t_mutex));
	if (shared->mutexes == NULL)
		return (deallocate_memory(shared, philosophers));
	*philosophers = malloc(n * sizeof(pthread_t));
	if (!*philosophers)
		return (deallocate_memory(shared, philosophers));
	shared->philos = malloc(n * sizeof(t_philo));
	if (shared->philos == NULL)
		return (deallocate_memory(shared, philosophers));
	ft_bzero(*philosophers, n * sizeof(pthread_t));
	ft_bzero(shared->mutexes, n * sizeof(t_mutex));
	ft_bzero(shared->philos, n * sizeof(t_philo));
	return (SUCCESS);
}

int32_t	get_config(t_config *cnf, char **argv)
{
	if (!*argv[1]|| !*argv[2] || !*argv[2] || !*argv[3] || !*argv[4])
		return (ERROR);
	cnf->nb_philo = ft_atoi(argv[1]);
	cnf->time_die = ft_atoi(argv[2]);
	cnf->time_eat = ft_atoi(argv[3]);
	cnf->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		if (!*argv[5])
			return (ERROR);
		cnf->minimum_servings = ft_atoi(argv[5]);
	}
	else
		cnf->minimum_servings = -1;
	if (cnf->nb_philo < 0 || cnf->nb_philo > 2047)
		return (ERROR);
	if (cnf->time_die < 0 || cnf->time_eat < 0 || cnf->time_sleep < 0)
		return (ERROR);
	if (argv[5])
		if (cnf->minimum_servings < 1)
			return (ERROR);
	return (SUCCESS);
}
