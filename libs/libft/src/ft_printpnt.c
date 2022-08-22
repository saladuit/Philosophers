/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_printpnt.c                                   |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/19 16:00:35 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/22 09:16:41 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_printpnt(size_t *len, unsigned long ul)
{
	char	*result;

	ft_putstr_fd("0x", 1);
	result = ft_ultoh(ul);
	ft_putstr_fd(result, 1);
	*len += ft_strlen(result) + 2;
	free(result);
	return ;
}
