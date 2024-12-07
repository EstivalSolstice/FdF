/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:24:43 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 11:30:37 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_fdf *fdf)
{
	t_camera	*cam;
	t_map_data	*map;

	cam = &fdf->cam;
	map = &fdf->map;
	if (keycode == 53)
		close_window(fdf);
	else
	{
		handle_camera_movement(keycode, cam);
		handle_camera_rotation(keycode, cam);
		handle_preset_views(keycode, cam, map);
		handle_zoom(keycode, cam);
	}
	redraw(fdf);
	return (0);
}

void	validate_input(t_fdf *fdf)
{
	fdf->render.mlx_ptr = mlx_init();
	if (!fdf->render.mlx_ptr)
	{
		ft_putstr_fd("Error: Failed to initialize MiniLibX.\n", 2);
		exit(EXIT_FAILURE);
	}
	fdf->render.win_ptr = mlx_new_window(fdf->render.mlx_ptr, 1200, 800, "FdF");
	if (!fdf->render.win_ptr)
	{
		ft_putstr_fd("Error: Failed to create a window.\n", 2);
		exit(EXIT_FAILURE);
	}
	fdf->render.img.ptr = mlx_new_image(fdf->render.mlx_ptr, 1200, 800);
	if (!fdf->render.img.ptr)
	{
		ft_putstr_fd("Error: Failed to create a new image.\n", 2);
		mlx_destroy_window(fdf->render.mlx_ptr, fdf->render.win_ptr);
		exit(EXIT_FAILURE);
	}
	fdf->render.img.data = mlx_get_data_addr(fdf->render.img.ptr,
			&fdf->render.img.bits_per_pixel, &fdf->render.img.line_length,
			&fdf->render.img.endian);
	render_map(fdf);
	mlx_put_image_to_window(fdf->render.mlx_ptr, fdf->render.win_ptr,
		fdf->render.img.ptr, 0, 0);
}

int	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->render.mlx_ptr, fdf->render.win_ptr);
	exit(0);
	return (0);
}
