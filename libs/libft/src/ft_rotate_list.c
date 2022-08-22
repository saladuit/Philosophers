/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_rotate_list.c                                |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/07 20:28:56 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/15 18:04:46 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rotate_list(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst)->next;
	ft_lstadd_back(lst, *lst);
	*lst = tmp;
	return ;
}
