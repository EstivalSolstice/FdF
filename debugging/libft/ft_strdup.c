/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:22:06 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 19:14:08 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * duplicates the string src passed as a parameter
 * checks len. of str.; alloc mem for str.; iter. through str and copy to dst
 * NULL terminate dst and return pointer to dst
 */
char	*ft_strdup(const char *src)
{
	int		index;
	int		len;
	char	*dst;

	index = 0;
	len = ft_strlen(src);
	dst = malloc((len + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (src[index] != '\0')
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}
