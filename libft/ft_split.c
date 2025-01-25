/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:21:29 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:47:25 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_allocated_memory(char **result, int substr_index)
{
	int	index;

	index = 0;
	while (index < substr_index)
	{
		free(result[index]);
		index++;
	}
	free(result);
}

static int	count_str(const char *str, char delimiter)
{
	int	count;
	int	index;
	int	insubstr;

	count = 0;
	index = 0;
	insubstr = 0;
	while (str[index] != '\0')
	{
		if (str[index] != delimiter)
		{
			if (insubstr == 0)
			{
				count++;
				insubstr = 1;
			}
		}
		else
		{
			insubstr = 0;
		}
		index++;
	}
	return (count);
}

static int	substr_extract(const char *str, char c, char **result)
{
	int			substr_index;
	const char	*start;
	const char	*end;

	substr_index = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str == '\0')
			return (1);
		start = str;
		end = ft_strchr(str, c);
		if (end == NULL)
			end = str + ft_strlen(str);
		result[substr_index] = ft_substr(start, 0, end - start);
		if (result[substr_index] == NULL)
		{
			free_allocated_memory(result, substr_index);
			return (0);
		}
		substr_index++;
		str = end;
	}
	return (1);
}

/**
 * takes a pointer to a string and a delimiter as parameters
 * counts nbr of strings; allocates memory for array of strings
 * finds start and end of substr; calls ft_substr to copy substr to result
 * frees if mem alloc. fails; NULL terminate the array of strings
 * return pointer to array of strings
 */
char	**ft_split(char const *str, char c)
{
	int		substr_count;
	char	**result;

	if (str == NULL)
		return (NULL);
	substr_count = count_str(str, c);
	result = (char **)malloc((substr_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	if (!substr_extract(str, c, result))
		return (NULL);
	result[substr_count] = NULL;
	return (result);
}
