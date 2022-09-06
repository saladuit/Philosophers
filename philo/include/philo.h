/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.h                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/16 20:40:00 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/06 16:09:04 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_PHILOSOPHERS 200
# define MAX_FORKS MAX_PHILOSOPHERS
# define MIN_TIME 60
# define ERROR -1
# define DONE 1
# define MUTEX 9

# define TOOK_FORK "has taken a fork"
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

typedef enum e_mutexindex
{
	ID,
	BREED,
	START,
	VOICE,
	TIME,
	EAT,
	DEAD,
	SERVINGS,
	MUTERROR,
}	t_mutexindex;

typedef struct s_config
{
	int32_t	nb_philo;
	int64_t	time_die;
	int64_t	time_eat;
	int64_t	time_sleep;
	int32_t	minimum_servings;
}	t_config;

typedef struct s_shared
{	
	bool			dead;
	bool			start;
	bool			error;
	int64_t			start_time;
	int32_t			philos_done_eating;
	t_config		cnf;
	t_mutex			*mutexes;
	struct s_philo	*philos;
}	t_shared;

typedef	struct s_philo
{
	int32_t 	id;
	int64_t		last_time_eaten;
	int64_t		time_diff;
	int32_t		servings;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_shared	*shared;
}	t_philo;

//init
void	init_philos(t_shared *shared, int32_t count);
int32_t	get_config(t_config *cnf, char **argv);
//mutex
int32_t	init_mutexes(t_mutex **mutexes, int32_t count);
int32_t	clean_mutexes(t_mutex **mutexes, int32_t count);
int32_t	mutex_api(t_mutex *mutex, int32_t (*func) (void *), void *ptr);
//thread
int32_t	make_thread(pthread_t *thread, void *(*routine)(void *), void *shared);
int32_t	start_diner(t_shared *shared);
int32_t	clean_table(pthread_t *philosophers, int32_t count);
int32_t	join_thread(pthread_t *thread);
int32_t	clean_philosophers(pthread_t *philosophers, int32_t count);
int32_t	breed_philosophers(t_shared *shared, pthread_t **philosophers);
//routine
void	*philosopher(void *ptr);
//start
int32_t	philo(char **argv);
//memory
int32_t	allocate_memory(t_shared *shared, pthread_t **philosophers, int32_t n);
int32_t deallocate_memory(t_shared *shared, pthread_t **philosophers);
int32_t	clean_mutexes(t_mutex **mutexes, int32_t count);
int32_t	clean_shared(t_shared *shared, pthread_t **philosophers, int32_t count);
int32_t	join_philosophers(pthread_t *philosophers, int32_t count);
int32_t	clean_program(t_shared *shared, pthread_t **philosophers, int32_t count);
//utils
int64_t	time_in_ms(void);
#endif
