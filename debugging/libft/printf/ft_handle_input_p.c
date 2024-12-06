/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_input_p.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:21:55 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/15 23:12:27 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Converts an unsigned integer to lowercase hexadecimal and prints it.
 *
 * @param num The unsigned integer to convert.
 * @param count Pointer to the character count.
 * 
 * @return Returns 0 on success, or -1 on error.
 */
static int	ft_puthex_lower(unsigned long num, int *count)
{
	char	*hex_digits;
	int		write_ret;

	hex_digits = "0123456789abcdef";
	if (num >= 16)
	{
		if (ft_puthex_lower(num / 16, count) == -1)
			return (-1);
	}
	write_ret = ft_write_return_val(1, &hex_digits[num % 16], 1);
	if (write_ret == -1)
		return (-1);
	(*count)++;
	return (0);
}

int	ft_handle_input_p(va_list args, int *count)
{
	void	*p_val;

	p_val = va_arg(args, void *);
	if (p_val == NULL)
	{
		if (ft_write_return_val(1, "0x0", 3) == -1)
			return (-1);
		(*count) += 3;
	}
	else
	{
		if (ft_write_return_val(1, "0x", 2) == -1)
			return (-1);
		(*count) += 2;
		if (ft_puthex_lower((unsigned long)p_val, count) == -1)
			return (-1);
	}
	return (0);
}
