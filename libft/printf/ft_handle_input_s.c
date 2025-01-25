/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_input_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:21:46 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/12 22:33:00 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_input_s(va_list args, int *count)
{
	char	*str;
	int		index;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	index = 0;
	while (str[index] != '\0')
	{
		if (ft_write_return_val(1, &str[index], 1) == -1)
			return (-1);
		index++;
	}
	(*count) += index;
	return (0);
}
