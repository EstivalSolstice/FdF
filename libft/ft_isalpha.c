/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:14:16 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 15:21:36 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Check if argument c passed as parameter is an alphabetical character
 * Output is either 1 or 0 / true or false depending on the result
 */
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}
