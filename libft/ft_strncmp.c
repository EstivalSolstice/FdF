/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:22:46 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/17 16:51:06 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compares str1 and str2 for n anount of chars
 * if there's no dif then return 0; if yes then return the dif between strings
 */
int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned int	counter;

	counter = 0;
	if (n == 0 || (str1 == NULL && str2 == NULL))
		return (0);
	while ((str1[counter] != '\0' || str2[counter] != '\0') && counter < n)
	{
		if (str1[counter] != str2[counter])
		{
			return ((unsigned char)str1[counter]
				- (unsigned char)str2[counter]);
		}
		counter++;
	}
	return (0);
}
