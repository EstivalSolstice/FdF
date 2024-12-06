/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:26:35 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:53:38 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * checks if parameter passed as c is an upperc. char
 * if yes change it to lowerc. and return new one; if no return c
 */
int	ft_tolower(int c)
{
	int	n;

	n = 0;
	if (c >= 65 && c <= 90)
	{
		n = c + 32;
		return (n);
	}
	else
		return (c);
}
