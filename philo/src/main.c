/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   main.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:09:40 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/07 20:40:42 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_philo_error(USAGE));
	return (ft_philo_error(philo(argv)));
}
