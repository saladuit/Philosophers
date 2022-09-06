/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   init.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:03:41 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/06 14:33:54 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	get_config(t_config *cnf, char **argv)
{
	cnf->nb_philo = ft_atoi(argv[1]);
	cnf->time_die = ft_atoi(argv[2]);
	cnf->time_eat = ft_atoi(argv[3]);
	cnf->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		cnf->minimum_servings = ft_atoi(argv[5]); //add in error checks
	else
		cnf->minimum_servings = -1;
	return (SUCCESS);
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
