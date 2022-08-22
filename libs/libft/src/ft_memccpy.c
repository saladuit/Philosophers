/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_memccpy.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/06/23 15:11:59 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned const char	*s;
	unsigned char		*d;

	d = dest;
	s = src;
	while (n)
	{
		*d = *s;
		if (*s == (unsigned char)c)
			return (d + 1);
		d++;
		s++;
		n--;
	}
	return (NULL);
}
