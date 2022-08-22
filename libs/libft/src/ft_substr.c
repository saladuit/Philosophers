/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_substr.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:14:30 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= (size_t)start)
		return (ft_strdup(""));
	dest = ft_strnew(len);
	if (!dest)
		return (NULL);
	ft_memcpy((void *)dest, (void *)&(s[start]), len);
	return (dest);
}
