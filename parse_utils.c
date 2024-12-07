/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:01:44 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 11:29:25 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_count_words(char *line, char delimiter)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == delimiter && line[i] != '\0')
			i++;
		if (line[i] != delimiter && line[i] != '\0')
			count++;
		while (line[i] != delimiter && line[i] != '\0')
			i++;
	}
	return (count);
}

int	parse_hex(const char *str)
{
	int	result;

	result = 0;
	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	else if (*str == '#')
		str++;
	while (*str)
	{
		result *= 16;
		if (*str >= '0' && *str <= '9')
			result += *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			result += *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			result += *str - 'A' + 10;
		else
			return (0);
		str++;
	}
	return (result);
}

int	parse_line(char *line, t_row_data *row_data, int width)
{
	char	**nums;
	char	*comma;
	int		i;

	i = 0;
	nums = ft_split(line, ' ');
	if (!nums)
		return (printf("Error: ft_split failed\n"), 0);
	while (nums[i])
	{
		comma = ft_strchr(nums[i], ',');
		row_data->z_line[i] = ft_atoi(nums[i]);
		if (comma)
		{
			*comma = '\0';
			row_data->color_line[i] = parse_hex(comma + 1);
		}
		else
			row_data->color_line[i] = 0xFF00FF;
		free(nums[i]);
		i++;
	}
	if (i != width)
		return (printf("Error: Invalid row width\n"), free(nums), 0);
	return (free(nums), *(row_data->actual_width) = i, 1);
}
