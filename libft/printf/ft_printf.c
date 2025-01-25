/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:22:43 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/15 22:38:18 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	va_list		args;
	const char	*ptr;
	int			count;

	ptr = fmt;
	va_start(args, fmt);
	count = 0;
	while (*ptr != '\0')
	{
		if (*ptr == '%')
		{
			ptr++;
			if (ft_check_inputprintf(*ptr, args, &count) == -1)
				return (va_end(args), -1);
		}
		else
		{
			if (ft_write_return_val(1, ptr, 1) == -1)
				return (va_end(args), -1);
			count++;
		}
		ptr++;
	}
	return (va_end(args), count);
}
