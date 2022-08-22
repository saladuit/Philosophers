/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: saladin <saladin@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 17:29:41 by saladin       #+#    #+#                 */
/*   Updated: 2021/09/22 11:40:18 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
void	ft_printpct(size_t *len);
void	ft_printpnt(size_t *len, unsigned long ul);
void	ft_printhe_x(size_t *len, unsigned int ui);
void	ft_printhex(size_t *len, unsigned int ui);
void	ft_printudec(size_t *len, unsigned int n);
void	ft_printdec(size_t *len, int n);
void	ft_printstr(size_t *len, char *string);
void	ft_printchr(size_t *len, int c);
void	ft_cnvspc(int c, size_t *len, va_list ap);

#endif
