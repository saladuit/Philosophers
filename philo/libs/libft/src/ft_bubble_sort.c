/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_bubble_sort.c                                |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/07 17:36:03 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/14 20:59:38 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bubble_sort(const int len, int *integer)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (len < 2)
		return ;
	while (i < (size_t)len)
	{
		j = 0;
		while (j < (size_t)len - i - 1)
		{
			if (integer[j] > integer[j + 1])
				ft_swap(&integer[j], &integer[j + 1]);
			j++;
		}
		i++;
	}
}
