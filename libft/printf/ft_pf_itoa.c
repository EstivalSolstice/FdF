/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:15:39 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/27 16:14:16 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_fill_str(char *str, unsigned int num, int i)
{
	while (num > 0)
	{
		str[i--] = (num % 10) + '0';
		num = num / 10;
	}
}

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

/**
 * Converts an integer n passed as the parameter to a str
 * checks number of digits; allocs mem for str; assign neg value pos value
 * recurs. filling str with digits; adding remainder with modulu 
 * turning them into char; returning the pointer to resulting str
 */
char	*ft_pf_itoa(int n)
{
	int				len;
	char			*str;
	unsigned int	num;

	len = ft_num_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	else
		num = n;
	ft_fill_str(str, num, len - 1);
	return (str);
}
