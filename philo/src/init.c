/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   init.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:03:41 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/03 18:32:44 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	init_settings(t_philo *settings, char **argv)
{
	settings->nb_philo = ft_atoi(argv[1]);
	settings->time_die = ft_atoi(argv[2]);
	settings->time_eat = ft_atoi(argv[3]);
	settings->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		settings->minimum_servings = ft_atoi(argv[5]); //add in error checks
	else
		settings->eat_count = -1;
	return (SUCCESS);
}
