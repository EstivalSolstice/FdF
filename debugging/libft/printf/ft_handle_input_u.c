/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_input_u.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:22:30 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/12 22:33:07 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_fd_mod(unsigned int n, int fd)
{
	char	c;
	int		write_return;

	if (n >= 10)
	{
		if (ft_putnbr_fd_mod(n / 10, fd) == -1)
			return (-1);
	}
	c = n % 10 + '0';
	write_return = ft_write_return_val(fd, &c, 1);
	if (write_return == -1)
		return (-1);
	return (0);
}

static int	ft_num_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	ft_handle_input_u(va_list args, int *count)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	if (ft_putnbr_fd_mod(num, 1) == -1)
		return (-1);
	(*count) += ft_num_len(num);
	return (0);
}
