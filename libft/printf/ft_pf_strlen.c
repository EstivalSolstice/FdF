/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_strlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:22:33 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/27 16:14:31 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * gets passed a pointer to a string which canot be modified (const)
 * iter. through string and counts chars; adds + 1 for NULL; returns count
 */
int	ft_pf_strlen(const char *str)
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
