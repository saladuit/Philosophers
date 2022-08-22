/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   get_next_line.c                                 |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/19 16:04:45 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/26 16:51:05 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifdef DEBUG
# define STATIC static
#else
# define STATIC
#endif

char	*ft_protected_strdup(const char *s, const char *fn)
{
	char	*d;

	d = ft_strdup(s);
	if (!d)
		ft_merror(fn);
	return (d);
}

char	*ft_protected_strjoin(const char *s1, const char *s2, const char *fn)
{
	char	*d;

	d = ft_strjoin(s1, s2);
	if (!d)
		ft_merror(fn);
	return (d);
}

STATIC int	search_and_save(char **saved, char **line)
{
	char			*tmp;

	tmp = ft_strchr(*saved, '\n');
	if (!tmp)
		return (0);
	*tmp = '\0';
	*line = ft_protected_strdup(*saved, "Search_and_save()");
	*saved = ft_protected_strdup(tmp + 1, "Search_and_save()");
	return (1);
}

STATIC int	read_into_buffer(int fd, char *buffer, char **saved, char **line)
{
	ssize_t		ret;
	char		*tmp;

	while (true)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		if (*saved)
		{
			tmp = *saved;
			*saved = ft_protected_strjoin(tmp, buffer, "Read_into_buffer()");
			free(tmp);
			tmp = NULL;
		}
		else
			*saved = ft_protected_strdup(buffer, "Read_into_buffer()");
		if (search_and_save(saved, line))
			break ;
	}
	return (ret);
}

ssize_t	get_next_line(int fd, char **line)
{
	static char	*saved[FOPEN_MAX] = {NULL};
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		ret;

	if (!line || (fd < 0 || fd >= FOPEN_MAX) || BUFFER_SIZE <= 0)
		return (-1);
	if (saved[fd])
		if (search_and_save(&saved[fd], line))
			return (1);
	buffer[BUFFER_SIZE] = '\0';
	ret = read_into_buffer(fd, buffer, &saved[fd], line);
	if (ret != 0 || saved[fd] == NULL || saved[fd][0] == '\0')
	{
		if (!ret && *line)
			*line = NULL;
		return (ret);
	}
	*line = saved[fd];
	saved[fd] = NULL;
	return (1);
}
