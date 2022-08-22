/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_strmapi.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:13:31 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*dest;
	size_t		len;

	if ((s == 0) || (f == 0))
		return (0);
	len = ft_strlen(s);
	dest = ft_strnew(len);
	if (!dest)
		return (NULL);
	len = 0;
	while (s[len])
	{
		dest[len] = f(len, s[len]);
		len++;
	}
	return (dest);
}
