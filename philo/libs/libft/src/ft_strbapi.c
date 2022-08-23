/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_strbapi.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:12:47 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strbapi(char const *s, bool (*f)(int))
{
	size_t	i;
	size_t	len;

	if ((s == 0) || (f == 0))
		return (0);
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (!f(s[i]))
			return (false);
		i++;
	}
	return (true);
}
