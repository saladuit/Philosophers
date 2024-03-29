/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/10 21:38:27 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	did_someone_die(void *ptr)
{
	t_philo		*philos;
	t_shared	*shared;
	int64_t		last_eaten;
	int64_t		i;

	i = 0;
	shared = ptr;
	philos = shared->philos;
	while (i < shared->cnf.nb_philo)
	{
		pthread_mutex_lock(&shared->mutexes[TIME]);
		last_eaten = philos[i].last_time_eaten;
		pthread_mutex_unlock(&shared->mutexes[TIME]);
		if (time_in_ms() - last_eaten > shared->cnf.time_die && !philos[i].done)
		{
			pthread_mutex_lock(&shared->mutexes[VOICE]);
			philos[i].time_diff = time_diff_ms(shared->start_time, \
					time_in_ms());
			narrator(philos[i].time_diff, philos[i].id, DIED, shared);
			mutex_api(&shared->mutexes[DEAD], philo_has_died, shared);
			pthread_mutex_unlock(&shared->mutexes[VOICE]);
			return (DONE);
		}
		i++;
	}
	return (SUCCESS);
}

void	monitor_philosophers(t_shared *shared)
{
	while (true)
	{
		if (did_someone_die(shared))
			return ;
		if (mutex_api(&shared->mutexes[SERVINGS], check_servings, shared))
			return ;
	}
}

int32_t	check_argv(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_strbapi(argv[i], ft_isdigit))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int32_t	philo(char **argv)
{
	t_shared	shared;
	pthread_t	*philosophers;

	philosophers = NULL;
	ft_bzero(&shared, sizeof(t_shared));
	if (check_argv(&argv[1]) || get_config(&shared.cnf, argv))
		return (EINPUT);
	if (shared.cnf.nb_philo == 1)
	{
		printf("%d\t%d\t%s\n", 0, 1, TOOK_FORK);
		usleep(shared.cnf.time_die * 1000);
		printf("%ld\t%d\t%s\n", shared.cnf.time_die, 1, DIED);
		return (SUCCESS);
	}
	if (allocate_memory(&shared, &philosophers, shared.cnf.nb_philo))
		return (EMALLOC);
	if (init_mutexes(&shared.mutexes, shared.cnf.nb_philo + MUTEX))
		return (deallocate_memory(&shared, &philosophers));
	init_philos(&shared, shared.cnf.nb_philo);
	if (breed_philosophers(&shared, &philosophers))
		return (clean_shared(&shared, &philosophers, shared.cnf.nb_philo));
	monitor_philosophers(&shared);
	return (clean_program(&shared, &philosophers, shared.cnf.nb_philo));
}
