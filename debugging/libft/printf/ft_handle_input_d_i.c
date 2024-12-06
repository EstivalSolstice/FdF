/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_input_d_i.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:21:40 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/27 16:06:25 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static int	ft_putnbr_safe(int n)
{
	char	*num_str;
	int		write_return_val;

	num_str = ft_pf_itoa(n);
	if (!num_str)
		return (-1);
	write_return_val = ft_write_return_val(1, num_str, ft_pf_strlen(num_str));
	free(num_str);
	if (write_return_val == -1)
		return (-1);
	return (0);
}

int	ft_handle_input_d_i(va_list args, int *count)
{
	int	n;
	int	num_len;

	n = va_arg(args, int);
	num_len = ft_num_len(n);
	if (ft_putnbr_safe(n) == -1)
		return (-1);
	(*count) += num_len;
	return (0);
}
