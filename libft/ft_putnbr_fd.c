/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:20:31 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:46:29 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * takes a number and a file descriptor as input
 * checks for edge cases and negative numbers
 * recursive div by 10 until single digit then modulu 10 extract last
 * recursion unwinds and each digit is printed into fd in correct order
 */
void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}
