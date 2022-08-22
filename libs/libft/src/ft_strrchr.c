/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_strrchr.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:13:57 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p;
	char		*curr;
	size_t		i;

	i = 0;
	p = s;
	curr = NULL;
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	while (p[i])
	{
		if (p[i] == c)
			curr = (char *)p + i;
		i++;
	}
	return (curr);
}
