/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   time.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/07 17:15:03 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/07 17:26:28 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_mssleep(int64_t millisec, t_shared *shared)
{
	int64_t time_stamp;

	time_stamp = time_in_ms();
	while (time_in_ms() - time_stamp < millisec)
	{
		if (mutex_api(&shared->mutexes[DEAD], sharedbool, &shared->dead))
			return ;
		usleep(300);
	}
}

int64_t	time_diff_ms(int64_t start, int64_t end)
{
	return (end - start);
}

int64_t	time_in_ms(void)
{
	t_timeval	tv;

	gettimeofday(&tv,NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
