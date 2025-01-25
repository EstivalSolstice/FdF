/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:15:54 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 15:25:36 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Adds new to the beginning of lst; **lst is address of the head pointer
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
