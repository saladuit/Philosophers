/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   get_next_line.h                                 |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/19 22:23:35 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/22 15:50:30 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_line
{
	ssize_t	b_read;
	char	*tmp;
}	t_line;

ssize_t		get_next_line(int fd, char **line);

#endif
