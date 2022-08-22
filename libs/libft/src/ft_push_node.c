/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_push_node.c                                  |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/07 21:30:23 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/14 20:47:14 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_push_node(t_list **dest, t_list **src)
{
	t_list	*tmp;

	if (*src == NULL)
		return ;
	tmp = (*src)->next;
	ft_lstadd_front(dest, *src);
	*src = tmp;
}
