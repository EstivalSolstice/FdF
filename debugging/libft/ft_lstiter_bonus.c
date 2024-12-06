/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:16:14 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 15:26:51 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Takes a pointer to a LinkedList and function f as parameter
 * iter. through nodes in the list applies function f to each node
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*applyft;

	applyft = lst;
	while (applyft != NULL)
	{
		f(applyft->content);
		applyft = applyft->next;
	}
}
