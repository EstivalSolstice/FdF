/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:26:19 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:52:25 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks for last occurance of c in str
 * iterates through str; stores last occ. of c in locc
 * if nothing is found returns locc which is init. as NULL already
 */
char	*ft_strrchr(const char *str, int c)
{
	const char	*pstr;
	const char	*locc;

	pstr = str;
	locc = NULL;
	while (*pstr)
	{
		if (*pstr == (char)c)
			locc = pstr;
		pstr++;
	}
	if ((char)c == '\0')
		return ((char *)pstr);
	return ((char *)locc);
}
