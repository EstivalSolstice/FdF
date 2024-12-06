/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:22:25 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:50:19 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Appends src at the end of dst but at most dstsize amount of chars
 * NULL terminate dst in any case; return total length of dst with src
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = 0;
	while (dst_len < dstsize && dst[dst_len] != '\0')
	{
		dst_len++;
	}
	if (dst_len == dstsize)
		return (dstsize + src_len);
	while (src[i] != '\0' && (dst_len + i + 1) < dstsize)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if ((dst_len + i) < dstsize)
		dst[dst_len + i] = '\0';
	else if (dstsize > 0)
		dst[dstsize - 1] = '\0';
	return (dst_len + src_len);
}
