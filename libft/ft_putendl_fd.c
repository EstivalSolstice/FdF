/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:19:05 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:45:59 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes the string into the fd passed as parameter followed by a newline
 */
void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}
