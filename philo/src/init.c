/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   init.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:03:41 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/31 11:17:32 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	construct_settings(t_philo *settings, char **argv)
{
	settings->time_die = ft_atoi(argv[2]);
	settings->time_eat = ft_atoi(argv[3]);
	settings->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		settings->eat_count = ft_atoi(argv[5]); //add in error checks
	else
		settings->eat_count = -1;
	return (SUCCESS);
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

int32_t	init_settings(int32_t *count, t_philo *settings, char **argv)
{
	t_philo	standard;

	*count = ft_atoi(argv[1]);
	if (construct_settings(&standard, argv) == ERROR)
		return (ERROR);
	fill_settings(settings, &standard, *count);
	return (SUCCESS);
}
