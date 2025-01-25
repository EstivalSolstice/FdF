/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:15:59 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 15:26:07 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * iter. through LinkedList starting from node pointed to by *lst
 * del function to delete content; frees mem. for node
 * sets the original list pointer *lst to NULL after clearing
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*find_node;
	t_list	*find_next;

	if (!lst || !*lst)
		return ;
	find_node = *lst;
	while (find_node != NULL)
	{
		find_next = find_node->next;
		del(find_node->content);
		free(find_node);
		find_node = find_next;
	}
	*lst = NULL;
}
