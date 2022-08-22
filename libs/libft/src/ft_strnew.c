/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_strnew.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/21 20:37:03 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (size >= __SIZE_MAX__)
		return (NULL);
	str = ft_calloc(size + 1, sizeof(char));
	return (str);
}
