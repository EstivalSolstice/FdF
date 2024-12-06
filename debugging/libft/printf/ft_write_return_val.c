/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_return_val.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:26:16 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/16 17:13:07 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_return_val(int fd, const void *buf, size_t count)
{
	int	write_return_val;

	if (fd < 0)
		return (-1);
	write_return_val = write(fd, buf, count);
	if (write_return_val == -1)
		return (-1);
	return (write_return_val);
}
