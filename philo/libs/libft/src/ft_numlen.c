/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_numlen.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:09:08 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen(long long num)
{
	if (num < 0)
		num = -num;
	if (num < 10)
		return (1);
	if (num < 100)
		return (2);
	if (num < 1000)
		return (3);
	if (num < 10000)
		return (4);
	if (num < 100000)
		return (5);
	if (num < 1000000)
		return (6);
	return ((ft_numlen(num / 1000000)) + 6);
}
