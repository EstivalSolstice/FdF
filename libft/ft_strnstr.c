/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:26:11 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/17 17:07:21 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks first occurance of str needle in str haystack passed as parameters
 * limited to amount of char. len; iter. through haystack to find needle
 * returns NULL if needle is not in haystack; returns hayst. if needle is empty
 * if needle in hayst. returns ptr to first char of first occ in haystack
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack && len == 0)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] != '\0' && (i + j) < len
			&& haystack[i + j] == needle[j])
		{
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
