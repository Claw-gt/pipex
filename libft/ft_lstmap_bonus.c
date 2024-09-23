/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 22:21:19 by clagarci          #+#    #+#             */
/*   Updated: 2024/02/03 15:14:46 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*new_lst;
	t_list	*node;
	void	*aux;

	if (!lst || !f || !del)
		return (NULL);
	current = lst;
	new_lst = NULL;
	while (current != NULL)
	{
		aux = f(current->content);
		node = ft_lstnew(aux);
		if (node == NULL)
		{
			del (aux);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, node);
		current = current->next;
	}
	return (new_lst);
}
