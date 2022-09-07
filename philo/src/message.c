/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   message.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/07 11:51:36 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/07 12:06:03 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_philo_error(t_message code)
{
	if (!code)
		return (EXIT_SUCCESS);
	ft_error();
	ft_putendl_fd(philo_messages(code), STDERR_FILENO);
	return (EXIT_FAILURE);
}

const char	*philo_messages(t_message code)
{
	const char	*message[] = {
	[SUCCESS] =	"Exit Succes",
	[USAGE] = 	"./philo nb_philos time_die time_eat time_sleep [min_servings]",
	[EINPUT] =	"Invalid input",
	[EMALLOC] =	"Malloc failed",
	[EMUTEX] =	"Mutex initilization failed",
	[EPTHREAD] =	"Pthread creation failed",
	};

	return (message[code]);
}
