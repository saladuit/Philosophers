/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_putuint_fd.c                                 |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:12:25 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putuint_fd(unsigned int nb, int fd)
{
	char	*result;

	result = ft_uitoa(nb);
	ft_putstr_fd(result, fd);
	free(result);
	return ;
}
