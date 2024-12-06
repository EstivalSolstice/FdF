/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:56:58 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/06 16:32:46 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int ft_count_words(char *line, char delimiter)
// {
//     int count = 0;
//     int i = 0;

//     while (line[i])
//     {
//         while (line[i] == delimiter && line[i] != '\0')
//             i++;
//         if (line[i] != delimiter && line[i] != '\0')
//             count++;
//         while (line[i] != delimiter && line[i] != '\0')
//             i++;
//     }
//     return (count);
// }

// int parse_line(char *line, int *z_line, int width)
// {
//     char    **nums;
//     int     i;

//     nums = ft_split(line, ' ');
//     if (!nums)
//         return (0);
//     i = 0;
//     while (nums[i])
//     {
//         z_line[i] = ft_atoi(nums[i]);
//         free(nums[i]);
//         i++;
//     }
//     free(nums);
//     return (i == width);
// }

// int parse_map(const char *file_name, t_fdf *fdf)
// {
//     int     fd;
//     char    *line;
//     int     i;

//     fd = open(file_name, O_RDONLY);
//     if (fd < 0)
//         return (0);
//     i = 0;
// 	line = NULL;
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         if (i == 0)
//             fdf->map_width = ft_count_words(line, ' ');
//         fdf->z_values[i] = malloc(sizeof(int) * fdf->map_width);
//         if (!fdf->z_values[i] || !parse_line(line, fdf->z_values[i], fdf->map_width))
//         {
//             free(line);
// 			close(fd);
//             return (0);
//         }
//         free(line);
//         i++;
//     }
//     fdf->map_height = i;
//     close(fd);
//     return (1);
// }
