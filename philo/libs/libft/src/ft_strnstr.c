/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_strnstr.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:13:46 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(little);
	if (*little == '\0' || little == NULL || len == 0 || little == big)
		return ((char *)big);
	while (i < len)
	{
		if (!ft_strncmp(big + i, little, j) && i + j < len)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
