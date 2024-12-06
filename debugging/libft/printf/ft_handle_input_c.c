/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_input_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:21:36 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/12 21:06:01 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_input_c(va_list args, int *count)
{
	char	c;

	c = (char)va_arg(args, int);
	if (ft_write_return_val(1, &c, 1) == -1)
		return (-1);
	(*count)++;
	return (0);
}
