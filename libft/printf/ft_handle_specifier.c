/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_specifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:40:56 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/18 16:12:00 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_specifier(const char fmt, va_list args, int *count)
{
	if (fmt == 'c')
		return (ft_handle_input_c(args, count));
	if (fmt == 's')
		return (ft_handle_input_s(args, count));
	if (fmt == 'p')
		return (ft_handle_input_p(args, count));
	if (fmt == 'd' || fmt == 'i')
		return (ft_handle_input_d_i(args, count));
	if (fmt == 'u')
		return (ft_handle_input_u(args, count));
	if (fmt == 'x')
		return (ft_handle_input_x(args, count));
	if (fmt == 'X')
		return (ft_handle_input_xu(args, count));
	return (-2);
}
