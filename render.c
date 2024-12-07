/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:24:29 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 11:38:24 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_map(t_fdf *fdf)
{
	t_render_context	*render;
	t_map_data			*map;
	int					y;

	render = &fdf->render;
	map = &fdf->map;
	mlx_clear_window(render->mlx_ptr, render->win_ptr);
	if (render->img.ptr)
		mlx_destroy_image(render->mlx_ptr, render->img.ptr);
	render->img.ptr = mlx_new_image(render->mlx_ptr, 1200, 800);
	render->img.data = mlx_get_data_addr(render->img.ptr,
			&render->img.bits_per_pixel, &render->img.line_length,
			&render->img.endian);
	y = 0;
	while (y < map->height)
	{
		process_row(fdf, map, y);
		y++;
	}
}

void	redraw(t_fdf *fdf)
{
	mlx_clear_window(fdf->render.mlx_ptr, fdf->render.win_ptr);
	mlx_destroy_image(fdf->render.mlx_ptr, fdf->render.img.ptr);
	fdf->render.img.ptr = mlx_new_image(fdf->render.mlx_ptr, 1200, 800);
	fdf->render.img.data = mlx_get_data_addr(fdf->render.img.ptr,
			&fdf->render.img.bits_per_pixel, &fdf->render.img.line_length,
			&fdf->render.img.endian);
	render_map(fdf);
	mlx_put_image_to_window(fdf->render.mlx_ptr, fdf->render.win_ptr,
		fdf->render.img.ptr, 0, 0);
}

void	draw_horizontal_line(t_fdf *fdf, t_point p1, int x, int y)
{
	t_map_data	*map;
	t_point		p2;

	map = &fdf->map;
	if (x < map->row_widths[y] - 1)
	{
		p2.x = x + 1;
		p2.y = y;
		p2.z = map->z_values[y][x + 1];
		p2.color = map->colors[y][x + 1];
		p2 = transform_point(fdf, p2);
		draw_line_dda(p1, p2, fdf);
	}
}

void	draw_vertical_line(t_fdf *fdf, t_point p1, int x, int y)
{
	t_map_data	*map;
	t_point		p3;

	map = &fdf->map;
	if (y < map->height - 1 && x < map->row_widths[y + 1])
	{
		p3.x = x;
		p3.y = y + 1;
		p3.z = map->z_values[y + 1][x];
		p3.color = map->colors[y + 1][x];
		p3 = transform_point(fdf, p3);
		draw_line_dda(p1, p3, fdf);
	}
}

void	process_row(t_fdf *fdf, t_map_data *map, int y)
{
	int		x;
	t_point	p1;

	x = 0;
	while (x < map->row_widths[y])
	{
		p1.x = x;
		p1.y = y;
		p1.z = map->z_values[y][x];
		p1.color = map->colors[y][x];
		p1 = transform_point(fdf, p1);
		draw_horizontal_line(fdf, p1, x, y);
		draw_vertical_line(fdf, p1, x, y);
		x++;
	}
}
