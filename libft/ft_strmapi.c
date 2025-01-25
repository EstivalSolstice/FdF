/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:22:40 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/10 02:18:15 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	unsigned int	str_len;
	char			*new_str;

	index = 0;
	str_len = ft_strlen(s);
	new_str = (char *)malloc((str_len + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (index < str_len)
	{
		new_str[index] = f(index, s[index]);
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}
