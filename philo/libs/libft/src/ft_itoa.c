/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_itoa.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:01:26 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int nb)
{
	size_t		len;
	char		*result;
	size_t		neg;
	long long	buffer;

	buffer = nb;
	len = ft_sgdnumlen(buffer);
	neg = 0;
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (0);
	if (buffer < 0)
	{
		buffer = -buffer;
		*result = '-';
		neg = 1;
	}
	while (len > neg)
	{
		len--;
		result[len] = (buffer % 10) + '0';
		buffer /= 10;
	}
	return (result);
}
