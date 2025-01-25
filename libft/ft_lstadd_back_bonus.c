/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:15:47 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 15:25:21 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Adds new to the end of lst
 * iter. through nodes until NULL; add a node there
 * adding value of new into the added node
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*findlast_node;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	findlast_node = *lst;
	while (findlast_node->next != NULL)
	{
		findlast_node = findlast_node->next;
	}
	findlast_node->next = new;
}
