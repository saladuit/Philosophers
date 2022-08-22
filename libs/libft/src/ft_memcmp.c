/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_memcmp.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:04:09 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*p1;
	unsigned const char	*p2;

	p1 = s1;
	p2 = s2;
	if (n == 0)
		return (0);
	while (n)
	{
		if (*p1 == *p2)
		{
			n--;
			p1++;
			p2++;
		}
		else
			return (*p1 - *p2);
	}
	return (0);
}
