/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_input_xu.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:22:39 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/16 17:03:47 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Converts an unsigned integer to uppercase hexadecimal and prints it.
 *
 * @param num The unsigned integer to convert.
 * @param count Pointer to the character count.
 * 
 * @return Returns 0 on success, or -1 on error.
 */
static int	ft_puthex_upper(unsigned int num, int *count)
{
	char	*hex_digits;
	int		write_return;

	hex_digits = "0123456789ABCDEF";
	if (num >= 16)
	{
		if (ft_puthex_upper(num / 16, count) == -1)
			return (-1);
	}
	write_return = ft_write_return_val(1, &hex_digits[num % 16], 1);
	if (write_return == -1)
		return (-1);
	(*count)++;
	return (0);
}

int	ft_handle_input_xu(va_list args, int *count)
{
	unsigned int	nx;

	nx = va_arg(args, unsigned int);
	if (ft_puthex_upper(nx, count) == -1)
		return (-1);
	return (0);
}
