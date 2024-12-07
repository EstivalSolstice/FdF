/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:58:56 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 06:33:49 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_camera(t_point *point, t_camera *cam)
{
	point->x -= cam->x;
	point->y -= cam->y;
	point->z -= cam->z;
}

void	apply_rotation(t_point *point, t_camera *cam)
{
	float	rad_x;
	float	rad_y;
	int		x;
	int		y;
	int		z;

	rad_x = cam->rotation_x * (M_PI / 180.0);
	rad_y = cam->rotation_y * (M_PI / 180.0);
	x = point->x;
	y = point->y;
	z = point->z;
	point->x = (int)(x * cos(rad_y) + z * sin(rad_y));
	point->z = (int)(-x * sin(rad_y) + z * cos(rad_y));
	point->y = (int)(y * cos(rad_x) - z * sin(rad_x));
	point->z = (int)(y * sin(rad_x) + z * cos(rad_x));
}

void	isometric_projection(t_point *point)
{
	float	iso;
	int		x;
	int		y;

	iso = 30.0 * (M_PI / 180.0);
	x = point->x;
	y = point->y;
	point->x = (int)((x - y) * cos(iso));
	point->y = (int)((x + y) * sin(iso) - point->z);
}

void	transform_and_project(t_fdf *fdf, t_point *point)
{
	apply_camera(point, &fdf->cam);
	apply_rotation(point, &fdf->cam);
	isometric_projection(point);
}

t_point	transform_point(t_fdf *fdf, t_point input)
{
	t_point	result;

	result.x = input.x * fdf->cam.scale;
	result.y = input.y * fdf->cam.scale;
	result.z = input.z * Z_SCALE;
	result.color = input.color;
	transform_and_project(fdf, &result);
	result.x += OFFSET_X;
	result.y += OFFSET_Y;
	return (result);
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

void	handle_camera_movement(int keycode, t_camera *cam)
{
	if (keycode == 0)
		cam->x += 10;
	else if (keycode == 2)
		cam->x -= 10;
	else if (keycode == 13)
		cam->y += 10;
	else if (keycode == 1)
		cam->y -= 10;
	else if (keycode == 34)
		cam->z -= 10;
	else if (keycode == 40)
		cam->z += 10;
	else if (keycode == 38)
	{
		cam->x += 10;
		cam->y -= 10;
	}
	else if (keycode == 37)
	{
		cam->x -= 10;
		cam->y += 10;
	}
}

void	handle_camera_rotation(int keycode, t_camera *cam)
{
	if (keycode == 123)
		cam->rotation_y -= 5.0;
	else if (keycode == 124)
		cam->rotation_y += 5.0;
	else if (keycode == 126)
		cam->rotation_x -= 5.0;
	else if (keycode == 125)
		cam->rotation_x += 5.0;
}

void	handle_preset_views(int keycode, t_camera *cam)
{
	if (keycode == 18)
	{
		cam->x = 0;
		cam->y = -500;
		cam->z = 500;
	}
	else if (keycode == 19)
	{
		cam->x = 500;
		cam->y = 0;
		cam->z = 500;
	}
	else if (keycode == 20)
	{
		cam->x = 0;
		cam->y = 0;
		cam->z = 1000;
	}
	else if (keycode == 21)
	{
		cam->rotation_x = 0.0;
		cam->rotation_y = 0.0;
	}
}

void	handle_zoom(int keycode, t_camera *cam)
{
	if (keycode == 24)
		cam->scale += 0.1;
	else if (keycode == 27)
		cam->scale -= 0.1;
}

int	key_hook(int keycode, t_fdf *fdf)
{
	t_camera	*cam;

	cam = &fdf->cam;
	if (keycode == 53)
		close_window(fdf);
	else
	{
		handle_camera_movement(keycode, cam);
		handle_camera_rotation(keycode, cam);
		handle_preset_views(keycode, cam);
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

void	put_pixel_to_image(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 1200 && y >= 0 && y < 800)
	{
		dst = fdf->render.img.data + (y * fdf->render.img.line_length
				+ x * (fdf->render.img.bits_per_pixel / 8));
		*(unsigned int *)dst = (unsigned int)color;
	}
}

void	draw_line_dda(t_point p1, t_point p2, t_fdf *fdf)
{
	t_dda	dda;
	int		i;

	dda.steps = (int)fmax(abs(p2.x - p1.x), abs(p2.y - p1.y));
	dda.x = p1.x;
	dda.y = p1.y;
	dda.x_inc = (float)(p2.x - p1.x) / dda.steps;
	dda.y_inc = (float)(p2.y - p1.y) / dda.steps;
	dda.color = p1.color;
	dda.color_inc = (float)(p2.color - p1.color) / dda.steps;
	i = 0;
	while (i <= dda.steps)
	{
		put_pixel_to_image(fdf, (int)roundf(dda.x), (int)roundf(dda.y),
			(int)dda.color);
		dda.x += dda.x_inc;
		dda.y += dda.y_inc;
		dda.color += dda.color_inc;
		i++;
	}
}

int	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->render.mlx_ptr, fdf->render.win_ptr);
	exit(0);
	return (0);
}
