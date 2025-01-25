/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:14:07 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 14:42:52 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**  
 * Check if argument c passed as parameter is alphab. or a digit
 * Output is either 1 or 0 / true or false depending on the result
*/
int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
