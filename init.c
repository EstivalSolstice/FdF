/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:25:11 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 11:28:52 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*initialize_fdf(void)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->map.width = 0;
	fdf->map.height = 0;
	fdf->map.z_values = NULL;
	fdf->map.colors = NULL;
	fdf->map.row_widths = NULL;
	fdf->cam.x = 0;
	fdf->cam.y = 0;
	fdf->cam.z = 0;
	fdf->cam.rotation_x = 0.0;
	fdf->cam.rotation_y = 0.0;
	fdf->cam.scale = 1.0;
	fdf->render.mlx_ptr = NULL;
	fdf->render.win_ptr = NULL;
	fdf->render.img.ptr = NULL;
	fdf->render.img.data = NULL;
	return (fdf);
}

void	free_fdf(t_fdf *fdf)
{
	int	i;

	if (fdf->map.z_values || fdf->map.colors)
	{
		i = 0;
		while (i < fdf->map.height)
		{
			if (fdf->map.z_values)
				free(fdf->map.z_values[i]);
			if (fdf->map.colors)
				free(fdf->map.colors[i]);
			i++;
		}
	}
	free(fdf->map.z_values);
	free(fdf->map.colors);
	free(fdf->map.row_widths);
	if (fdf->render.img.ptr && fdf->render.mlx_ptr)
		mlx_destroy_image(fdf->render.mlx_ptr, fdf->render.img.ptr);
	if (fdf->render.win_ptr && fdf->render.mlx_ptr)
		mlx_destroy_window(fdf->render.mlx_ptr, fdf->render.win_ptr);
	free(fdf);
}
