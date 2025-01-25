/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:19:10 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 17:45:45 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * takes a char and a file descriptor as input
 * writes the char into the fd
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
