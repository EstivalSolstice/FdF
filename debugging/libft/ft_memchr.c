/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:16:50 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:27:26 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks for first occurance of c in string
 * gen. ptr to str holds address to str; n is number of byte to check
 * counting down n until c is found or not; if not return NULL
 * if found it returns generic pointer to spec. byte
 */
void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	character;

	p = (unsigned char *)str;
	character = (unsigned char)c;
	while (n--)
	{
		if (*p == character)
			return (p);
		p++;
	}
	return (NULL);
}
