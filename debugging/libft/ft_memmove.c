/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:18:51 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:45:21 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies len amount chars from src to dst passed as parameters
 * making sure dst and src do not overlap and copying forward
 * if it could overlap it copies backwards from the end
 * returns pointer to mem. block dst
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (const unsigned char *)src;
	if (len == 0 || dst == src || (dst == NULL && src == NULL))
		return (dst);
	if (pdst < psrc || pdst >= (psrc + len))
	{
		while (len--)
		{
			*pdst++ = *psrc++;
		}
	}
	else
	{
		pdst = pdst + len;
		psrc = psrc + len;
		while (len--)
		{
			*(--pdst) = *(--psrc);
		}
	}
	return (dst);
}
