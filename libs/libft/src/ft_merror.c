/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_merror.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/22 16:02:39 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/26 16:48:23 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_merror(const char *function_name)
{
	ft_error();
	ft_putendl_fd("Malloc Fail in:", STDERR_FILENO);
	ft_putendl_fd(function_name, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
