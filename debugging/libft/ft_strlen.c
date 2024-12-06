/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:22:33 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:50:38 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * gets passed a pointer to a string which canot be modified (const)
 * iter. through string and counts chars; adds + 1 for NULL; returns count
 */
int	ft_strlen(const char *str)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		counter = counter + 1;
		str++;
	}
	return (counter);
}
