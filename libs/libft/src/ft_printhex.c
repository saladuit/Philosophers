/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_printhex.c                                   |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/19 16:03:13 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/22 09:07:38 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_printhex(size_t *len, unsigned int ui)
{
	char	*result;

	result = ft_uitoh(ui);
	ft_putstr_fd(result, 1);
	*len += ft_strlen(result);
	free(result);
	return ;
}
