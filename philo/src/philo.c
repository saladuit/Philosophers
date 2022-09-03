/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/03 18:37:44 by safoh        \___)=(___/                 */
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
    return ((end - start) * 1000) + ((end - start) / 1000);
}

//void	take_fork(t_mutex *fork, time_t time, int32_t id)
//{
//	pthread_mutex_lock(fork);
//	printf("%ld %d has taken a fork\n", time, id);
//	pthread_mutex_unlock(fork);
//}
//
//void	take_forks(t_shared *shared)
//{
//	t_shared *p;
//	take_fork(shared->mutexes.forks);
//}

int32_t	get_id(void *ptr)
{
	int32_t	id;
	
	((t_shared *)ptr)->id++;
	id = ((t_shared *)ptr)->id;
	((t_shared *)ptr)->settings[id - 1].id = id;
	return (((t_shared *)ptr)->id);
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
	int32_t id;
	int64_t	startms;

	id = ((t_philo *)ptr)->id;
	startms = ((t_philo *)ptr)->start_time;
	narrator(time_diff_ms(startms, time_in_ms()), id, EATING);
	((t_philo *)ptr)->eat_count--;
	usleep(((t_philo *)ptr)->time_eat * 1000);
	return (0);
}

int32_t died(void *ptr)
{
	narrator(time_in_ms(), ((t_philo *)ptr)->id, DIED);
	return (0);
}

int32_t	check_eat_count(void *p)
{
	t_philo	*settings;

	settings = (t_philo *)p;	
	if (settings->eat_count == 0)
		return (DONE);
	return (SUCCESS);
}

void	start_feasting(t_shared *shared)
{
	int32_t	id;
	id = mutex_api(&shared->mutexes[ID], get_id, shared);
	if (id == ERROR)
		return ;
	shared->settings[id - 1].start_time = shared->start_time;
	while (1)
	{
		if (mutex_api(&shared->mutexes[VOICE], eat, &shared->settings[id - 1]))
			return ;

		if (mutex_api(&shared->mutexes[VOICE], check_eat_count, &shared->settings[id - 1]))
			return ;
	}
}

int32_t	check_all_eat_count(void *p)
{
	t_shared	*shared;
	int32_t		i;
	int32_t		actions_left;

	shared = (t_shared *)p;
	i = 0;
	actions_left = 0;
	while (i < shared->count)
	{
		actions_left += shared->settings[i].eat_count;
		i++;
	}
	if (actions_left == 0)
		return (DONE);
	return (SUCCESS);
}

void	*philosopher(void *p)
{
	t_shared	*shared;
	int32_t		start;

	shared = (t_shared *)p;
	while (1)
	{
		if (mutex_api(&shared->mutexes[START], isdead, shared))
			return (NULL);
		start = mutex_api(&shared->mutexes[START], canstart, shared);
		if (start == true)
			break ;
		if (start == ERROR)
			return (NULL);
	}
	start_feasting(shared);
	return (NULL);
}

void	monitor_philosophers(t_shared *shared)
{
	int32_t	i;

	i = 0;
	while (1)
	{
		if (mutex_api(&shared->mutexes[DEAD], isdead, shared))
			if (mutex_api(&shared->mutexes[VOICE], died, shared))
				return ;
		if (mutex_api(&shared->mutexes[VOICE], check_all_eat_count, shared) == 1)
			return ;
	}
}

int32_t	philo(char **argv)
{
	t_shared	shared;
	pthread_t	philosophers[MAX_PHILOSOPHERS];

	ft_bzero(&shared, sizeof(t_shared));
	if (init_settings(&shared.cnf, argv) == ERROR)
		return (ERROR);
	if (init_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX))
		return (destroy_mutexes(shared.mutexes, shared.cnf.nb_philo + MUTEX));
	if (breed_philosophers(&shared) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.cnf.count + MUTEX));
	monitor_philosophers(&shared);
	if (clean_philosophers(&shared) == ERROR)
		return (destroy_mutexes(shared.mutexes, shared.cnf.count + MUTEX));
	destroy_mutexes(shared.mutexes, shared.cnf.count + MUTEX);
	return (SUCCESS);
}
