/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_lstmap.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:02:49 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursion(t_list *lst, void *(*f)(void *), t_list *new)
{
	if (lst == NULL)
		return ;
	ft_lstadd_back(&new, ft_lstnew(f(lst->content)));
	lst = lst->next;
	recursion(lst, f, new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;

	if (lst == NULL)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	lst = lst->next;
	recursion(lst, f, new);
	if (del)
		ft_lstiter(lst, del);
	return (new);
}
