/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_strtoupper.c                                 |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:14:22 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtoupper(char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		string[i] = ft_toupper(string[i]);
		i++;
	}
	return ;
}
