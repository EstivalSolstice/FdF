/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:20:41 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:46:49 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * takes pointer to string and fd as input
 * iter. through string and writing it into the fd
 */
void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
