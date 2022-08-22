/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   philo.h                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/16 20:40:00 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/08/22 18:24:56 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# include <libft.h>


typedef enum e_message
{
	SUCCESS,
	USAGE,
	MALLOC,
}	t_message;

void	philo(void);
#endif
