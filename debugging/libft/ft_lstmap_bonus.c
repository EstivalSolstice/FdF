/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:16:32 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 15:28:04 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates a new list applying function f on the linkedlist lst
 * if mem. alloc fails it uses function del and lstclear and returns NULL
 * iter. through nodes; using lstnew to create new node
 * adding new node at end of new_list using lstadd_back
 * returns pointer to new list
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*iter_lst;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	iter_lst = lst;
	if (f == NULL || del == NULL)
		return (NULL);
	while (iter_lst != NULL)
	{
		new_content = f(iter_lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		iter_lst = iter_lst->next;
	}
	return (new_list);
}
