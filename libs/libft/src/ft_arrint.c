/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_arrint.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/14 20:46:57 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

const int	*ft_arrint(const int *array, const int num, const int len)
{
	size_t	i;

	i = 0;
	while (i < (size_t)len)
	{
		if (array[i] == num)
			return (array + i);
		i++;
	}
	return (NULL);
}
