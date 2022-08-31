/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.h                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/16 20:40:00 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/31 11:01:30 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_PHILOSOPHERS 200
# define MAX_TIM 60
# define ERROR -1
# define DEAD 1
# define ALIVE 0

# define TOOK_FORK "has taken a fork\n"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

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

typedef struct timeval t_timeval;
typedef pthread_mutex_t t_mutex;

typedef enum e_message
{
	SUCCESS,
	USAGE,
	MALLOC,
}	t_message;

typedef	struct s_philo
{
	time_t	time_die;
	time_t	time_eat;
	time_t	time_sleep;
	int32_t	eat_count;
	int32_t	left_fork;
	int32_t	right_fork;
}	t_philo;

typedef struct s_mutexes
{
	t_mutex		forks[MAX_PHILOSOPHERS];
	t_mutex		voice;
	t_mutex		id;
	t_mutex		dead;
	t_mutex		start;
	t_mutex		grab;
}	t_mutexes;

typedef struct s_shared
{	
	int32_t		id;
	int32_t		count;
	bool		dead;
	bool		start;
	t_philo		settings[MAX_PHILOSOPHERS];
	pthread_t	philosophers[MAX_PHILOSOPHERS];
	t_mutexes	mutexes;
}	t_shared;

//init
int32_t	init_settings(t_philo *settings, char **argv);
void	fill_settings(t_philo *settings, t_philo *standard, int32_t count);
void	construct_settings(t_philo *settings, char **argv);
//mutex
int32_t	init_mutexes(t_mutexes	*mutexes, int32_t count);
int32_t	destroy_mutexes(t_mutexes *mutexes, int32_t count, int32_t lvl);
int32_t	mutex_api(t_mutex *mutex, int32_t (*f) (t_shared *), t_shared *shared);
//thread
int32_t	make_thread(void *(*routine)(void *), void *shared, pthread_t *thread);
int32_t	start_diner(t_shared *shared);
int32_t	clean_table(pthread_t *philosophers, int32_t count);
int32_t	join_thread(pthread_t *thread);
int32_t	breed_philosophers(t_shared *shared);
//routine
void	*philosopher(void *p);
//start
int32_t	philo(char **argv);
#endif
