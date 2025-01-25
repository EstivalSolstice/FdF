/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:12:57 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 15:18:18 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * takes a pointer to a string as the input
 * iter. through the str; skips white spaces; checks if next char is + or -
 * skips +: if - then dashes variable is switched to -1
 * multiply by 10 to shift to the next nbr; change nbr to int to cmp
 */
int	ft_atoi(const char *str)
{
	int	result;
	int	dashes;

	result = 0;
	dashes = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			dashes = -dashes;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * dashes);
}
