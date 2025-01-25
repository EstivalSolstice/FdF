/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:22:19 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/11 14:07:03 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dst, const char *src)
{
	char	*start;

	start = dst;
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (start);
}

static char	*ft_strcat(char *dst, const char *src)
{
	char	*start;

	start = dst;
	while (*dst != '\0')
	{
		dst++;
	}
	while (*src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (start);
}

/**
 * contatenate str 1 and str 2 passed as parameters
 * check len of each str to alloc mem
 * strcpy copies s1 into newstr; strcat starts at NULL left from strcpy
 * returns pointer to a new NULL terminated string 
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, (char *)s1);
	ft_strcat(new_str, (char *)s2);
	return (new_str);
}
