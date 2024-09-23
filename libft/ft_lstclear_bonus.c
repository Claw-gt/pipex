/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:46:47 by clagarci          #+#    #+#             */
/*   Updated: 2024/02/03 15:12:52 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	if (lst != NULL && del != NULL)
	{
		current = *lst;
		while (current != NULL)
		{
			temp = current;
			del(current->content);
			current = current->next;
			free (temp);
		}
		free (current);
		*lst = NULL;
	}
}
