/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_printf.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/19 16:02:55 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/22 09:08:00 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	printpars(const char *format, size_t *len, va_list ap)
{
	size_t	i;

	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			ft_cnvspc(format[i + 1], len, ap);
			i += 2;
		}
		else
		{
			ft_printchr(len, format[i]);
			i++;
		}
	}
	return ;
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	len;

	len = 0;
	if (!format)
		return (0);
	va_start(ap, format);
	printpars(format, &len, ap);
	va_end(ap);
	return (len);
}
