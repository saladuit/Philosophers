/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_ultoh.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:14:53 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	hexlen(unsigned long n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		size++;
	}
	return (size);
}

char	*ft_ultoh(unsigned long n)
{
	const char	hex[17] = "0123456789abcdef";
	char		*result;
	size_t		len;
	size_t		i;

	len = hexlen(n);
	i = 0;
	result = ft_calloc(len + 1, sizeof(char));
	while (i < len)
	{
		result[len - 1] = hex[n % 16];
		n /= 16;
		len--;
	}
	return (result);
}
