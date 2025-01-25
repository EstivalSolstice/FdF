/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:26:28 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/11 14:10:45 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

static int	ft_is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

/**
 * Removes the chars in set at end and begin. from string s
 * check forward and backward to find end and start of trimmedstr
 * allocs mem. for trimmedstr; copies inside and NULL terminates
 * returns pointer to the now trimmed new string
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	char		*trimmed_string;
	size_t		len;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	while (*start && ft_is_in_set(*start, set))
	{
		start++;
	}
	end = s1 + ft_strlen(s1) - 1;
	while (end > start && ft_is_in_set(*end, set))
	{
		end--;
	}
	len = (size_t)(end - start + 1);
	trimmed_string = (char *)malloc(len + 1);
	if (!trimmed_string)
		return (NULL);
	ft_strncpy(trimmed_string, start, len);
	trimmed_string[len] = '\0';
	return (trimmed_string);
}
