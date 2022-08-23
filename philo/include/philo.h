/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.h                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/16 20:40:00 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/23 15:35:12 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
//void	free(void *ptr);

# include <stdio.h>
//int	printf(const char * restrict format, ...);

# include <string.h>
//void	*memset(void *b, int c, size_t len);

 #include <sys/time.h>
//int	gettimeofday(struct timeval *restrict tp, void *restrict tzp);
//The system's notion of the current Greenwich time and the current time zone is
//obtained with the gettimeofday() call, and set with the settimeofday() call.
//The time is expressed in seconds and microseconds since midnight (0 hour),
//January 1, 1970.

# include <pthread.h>
//int	pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//            void *(*start_routine)(void *), void *arg)
//            Creates a new thread of execution.

//int	pthread_detach(pthread_t thread)
//            Marks a thread for deletion.

//int	pthread_join(pthread_t thread, void **value_ptr)
//           Causes the calling thread to wait for the termination of the specified
//          thread.

//int	pthread_mutex_init(pthread_mutex_t *mutex,
//             const pthread_mutexattr_t *attr)
//            Initialize a mutex with specified attributes.

//int	pthread_mutex_destroy(pthread_mutex_t *mutex)
//             Destroy a mutex.

//int	pthread_mutex_lock(pthread_mutex_t *mutex)
//             Lock a mutex and block until it becomes available.

//int	pthread_mutex_unlock(pthread_mutex_t *mutex)
//             Unlock a mutex.

# include <unistd.h>
//ssize_t	write(int fildes, const void *buf, size_t nbyte);
//int		usleep(useconds_t microseconds);

# include <libft.h>


typedef enum e_message
{
	SUCCESS,
	USAGE,
	MALLOC,
}	t_message;

void	philo(void);
#endif
