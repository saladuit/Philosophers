/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_rev_rotate_list.c                            |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/07 20:37:10 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/14 20:54:49 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_second_last(t_list *lst)
{
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_rev_rotate_list(t_list **lst)
{
	t_list	*second_last;

	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	second_last = ft_second_last(*lst);
	second_last->next->next = *lst;
	*lst = second_last->next;
	second_last->next = NULL;
	return ;
}
