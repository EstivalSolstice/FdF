/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:13:57 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 15:19:26 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates mem. for array of elements; each has spec. size; alreadz. 0 initi.
 * check for overflow when it mulitpleis count and size to det. for malloc
 * return a generic(void) pointer to alloc. memory
 */
void	*ft_calloc(size_t count, size_t size)
{
	size_t	t_size;
	void	*memory;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	t_size = count * size;
	memory = malloc(t_size);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, t_size);
	return (memory);
}
