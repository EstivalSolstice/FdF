/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_inputprintf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:21:30 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/15 22:40:40 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_inputprintf(const char fmt, va_list args, int *count)
{
	int	result;

	result = ft_handle_specifier(fmt, args, count);
	if (result != -2)
		return (result);
	if (fmt == '%')
	{
		if (ft_write_return_val(1, "%", 1) == -1)
			return (-1);
		(*count)++;
		return (0);
	}
	if (ft_write_return_val(1, "%", 1) == -1 || ft_write_return_val(1, &fmt,
			1) == -1)
		return (-1);
	(*count) += 2;
	return (0);
}
