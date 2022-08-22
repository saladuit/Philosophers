/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_cnvspc.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: saladuit <safoh@student.codam.nl>          //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/20 19:58:18 by saladuit     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/22 09:09:08 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_cnvspc(int c, size_t *len, va_list ap)
{
	if (c == 'c')
		ft_printchr(len, va_arg(ap, int));
	else if (c == 's')
		ft_printstr(len, va_arg(ap, char *));
	else if (c == 'i' || c == 'd')
		ft_printdec(len, va_arg(ap, int));
	else if (c == 'u')
		ft_printudec(len, va_arg(ap, unsigned int));
	else if (c == 'x')
		ft_printhex(len, va_arg(ap, unsigned int));
	else if (c == 'X')
		ft_printhe_x(len, va_arg(ap, unsigned int));
	else if (c == 'p')
		ft_printpnt(len, va_arg(ap, unsigned long));
	else if (c == '%')
		ft_printpct(len);
	return ;
}
