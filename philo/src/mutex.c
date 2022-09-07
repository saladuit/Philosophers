/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   mutex.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/30 14:09:26 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/07 17:58:52 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	check_servings(void *ptr)
{
	t_shared	*shared;

	shared = (t_shared *)ptr;
	if (shared->philos_done_eating == shared->cnf.nb_philo)
		return (DONE);
	return (SUCCESS);
}

int32_t	philo_has_died(void *ptr)
{
	t_shared	*shared;

	shared = (t_shared *)ptr;
	shared->dead = true;
	return (SUCCESS);
}

int32_t	sharedbool(void *ptr)
{
	bool	*status;

	status = (bool *)ptr;
	return (*status);
}

//int32_t	isdead(void *ptr)
//{
//	t_shared	*shared;
//
//	shared = (t_shared *)ptr;
//	return (shared->dead);
//}
//
//int32_t	checkerror(void *ptr)
//{
//	t_shared	*shared;
//
//	shared = (t_shared *)ptr;
//	return (shared->error);
//}
//
//int32_t	canstart(void *ptr)
//{
//	t_shared	*shared;
//
//	shared = (t_shared *)ptr;
//	return (shared->start);
//}

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
