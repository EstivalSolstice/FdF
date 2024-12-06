/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:16:55 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:44:16 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * compares bytes in str1 and str2, n is size of strs passed as parameters
 * iterates through both strings unti lit reaches the NULL terminator
 * returns the diffference if not the same or 0 if they are
 */
int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char		*sptr1;
	const unsigned char	*sptr2;
	size_t				i;

	sptr1 = (unsigned char *)str1;
	sptr2 = (const unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (sptr1[i] != sptr2[i])
			return (sptr1[i] - sptr2[i]);
		i++;
	}
	return (0);
}
