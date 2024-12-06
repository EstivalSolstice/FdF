/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:01:44 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/06 16:32:51 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// t_fdf *init_fdf(void)
// {
//     t_fdf *fdf = malloc(sizeof(t_fdf));
//     if (!fdf)
//         return NULL;

//     fdf->mlx_ptr = NULL;
//     fdf->win_ptr = NULL;
//     fdf->img_ptr = NULL;
//     fdf->img_data = NULL;
//     fdf->z_values = NULL;
//     fdf->map_width = 0;
//     fdf->map_height = 0;
// 	fdf->bits_per_pixel = 0;
// 	fdf->line_length = 0;
// 	fdf->endian = 0;

//     return (fdf);
// }

// void free_fdf(t_fdf *fdf)
// {
//     int i;

//     for (i = 0; i < fdf->map_height; i++)
//         free(fdf->z_values[i]);
//     free(fdf->z_values);
//     if (fdf->img_ptr)
//         mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
//     if (fdf->win_ptr)
//         mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
//     free(fdf);
// }

