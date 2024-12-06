/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:17:22 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:44:46 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies n number of bytes from src to dst passed as parameters
 * setting ptrs on start of src and dst ;it needs to be cast as its void *
 * copying until n is 0; returns pointer to memory block dst
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdest;

	psrc = (unsigned char *)src;
	pdest = (unsigned char *)dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n--)
	{
		*pdest = *psrc;
		psrc++;
		pdest++;
	}
	return (dst);
}
