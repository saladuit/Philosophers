/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   mutex.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:09:26 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/06 14:35:17 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	mutex_api(t_mutex *mutex, int32_t (*func) (void *), void *ptr)
{
	int32_t	result;

	if (pthread_mutex_lock(mutex))
		return (ERROR);
	result = func(ptr);
	if (pthread_mutex_unlock(mutex))
		return (ERROR);
	return (result);
}
