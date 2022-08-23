/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/08/22 18:10:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/23 15:45:32 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
void *work(void * p) {
	if (p == NULL)
		return (NULL);
	return (NULL);
}
void	philo(void)
{
	pthread_t philosopher;

	philosopher = NULL;
	if (pthread_create(&philosopher, NULL, work, NULL))
		printf("A thread error occured\n");
}
