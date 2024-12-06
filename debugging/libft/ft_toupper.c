/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:26:51 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:54:00 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * checks if parameter passed as c is an lowerc. char
 * if yes change it to upperc. and return new one; if no return c
 */
int	ft_toupper(int c)
{
	int	n;

	n = 0;
	if (c >= 97 && c <= 122)
	{
		n = c - 32;
		return (n);
	}
	else
		return (c);
}
