/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:16:05 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 15:26:27 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Takes a pointer to a node and function del as parameter
 * takes node as parameter for function del and frees its memory
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	del(lst->content);
	free(lst);
}
