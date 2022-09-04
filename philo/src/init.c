/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   init.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:03:41 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/04 11:23:18 by safoh        \___)=(___/                 */
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
