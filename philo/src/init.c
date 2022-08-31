/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   init.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:03:41 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/31 10:37:45 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

int32_t	init_settings(t_philo *settings, char **argv)
{
	t_philo	standard;
	int32_t	count;

	count = ft_atoi(argv[1]);
	construct_settings(&standard, argv);
	fill_settings(settings, &standard, count);
	return (count);
}
