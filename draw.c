/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:58:56 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/06 20:28:18 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void isometric_projection(int *x, int *y, int z)
{
    int prev_x = *x;
    int prev_y = *y;
	
	float angle_degrees = 30.0;
    float angle_radians = angle_degrees * (M_PI / 180.0);

    *x = (int)((prev_x - prev_y) * cos(angle_radians));
    *y = (int)((prev_x + prev_y) * sin(angle_radians) - z);

    // // *x = (int)((prev_x - prev_y) * cos(0.523599));
	// *x = (int)((prev_x - prev_y) * 30 * (M_PI / 180));
    // // *y = (int)((prev_x + prev_y) * sin(0.523599) - z);
	// *y = (int)((prev_x + prev_y) * 30 * (M_PI / 180) - z);
}

void put_pixel_to_image(t_fdf *fdf, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < 800 && y >= 0 && y < 600)
    {
        dst = fdf->img_data + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
        *(unsigned int *)dst = (unsigned int)color;
    }
}

void draw_line_dda(t_point p1, t_point p2, t_fdf *fdf)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    int steps = (int)fmaxf(fabsf(dx), fabsf(dy));
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    float x = p1.x;
    float y = p1.y;
	// double dx = p2.x - p1.x;
    // double dy = p2.y - p1.y;
    // int steps = (int)fmax(fabs(dx), fabs(dy));
    // double x_inc = dx / steps;
    // double y_inc = dy / steps;
    // double x = p1.x;
    // double y = p1.y;
	float color_inc = (float)(p2.color - p1.color) / steps;
    float current_color = p1.color;

//     for (int i = 0; i <= steps; i++)
//     {
//         put_pixel_to_image(fdf, (int)roundf(x), (int)roundf(y), 0xFFFFFF);
//         x += x_inc;
//         y += y_inc;
//     }
// }
	for (int i = 0; i <= steps; i++)
    {
        put_pixel_to_image(fdf, (int)roundf(x), (int)roundf(y), (int)current_color);
        x += x_inc;
        y += y_inc;
        current_color += color_inc;
    }
}

int close_window(t_fdf *fdf)
{
    mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
    exit(0);
    return (0);
}

void render(t_fdf *fdf)
{
    fdf->mlx_ptr = mlx_init();
    if (!fdf->mlx_ptr)
    {
        ft_putstr_fd("Error: Failed to initialize MiniLibX.\n", 2);
        exit(EXIT_FAILURE);
    }

    fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 800, 600, "FdF");
    if (!fdf->win_ptr)
    {
        ft_putstr_fd("Error: Failed to create a window.\n", 2);
        exit(EXIT_FAILURE);
    }

    fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, 800, 600);
    if (!fdf->img_ptr)
    {
        ft_putstr_fd("Error: Failed to create a new image.\n", 2);
        mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
        exit(EXIT_FAILURE);
    }

    fdf->img_data = mlx_get_data_addr(fdf->img_ptr,
                                      &fdf->bits_per_pixel,
                                      &fdf->line_length,
                                      &fdf->endian);
    if (!fdf->img_data)
    {
        ft_putstr_fd("Error: Failed to get image data address.\n", 2);
        mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
        mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
        exit(EXIT_FAILURE);
    }
    for (int y = 0; y < fdf->map_height; y++)
    {
        for (int x = 0; x < fdf->map_width; x++)
        {
			t_point p1 = {x, y, fdf->z_values[y][x], fdf->colors[y][x]};
            // t_point p1 = {x, y, fdf->z_values[y][x]};
            p1.z *= Z_SCALE;
            p1.x *= SCALE; p1.y *= SCALE;
			isometric_projection(&p1.x, &p1.y, p1.z);
            p1.x += OFFSET_X; p1.y += OFFSET_Y;

            if (x < fdf->map_width - 1)
            {
                t_point p2 = {x + 1, y, fdf->z_values[y][x + 1], fdf->colors[y][x + 1]};
				// t_point p2 = {x + 1, y, fdf->z_values[y][x + 1]};
				p2.z *= Z_SCALE;
                p2.x *= SCALE; p2.y *= SCALE;
				isometric_projection(&p2.x, &p2.y, p2.z);
                p2.x += OFFSET_X; p2.y += OFFSET_Y;
                draw_line_dda(p1, p2, fdf);
            }

            if (y < fdf->map_height - 1)
            {
				t_point p3 = {x, y + 1, fdf->z_values[y + 1][x], fdf->colors[y + 1][x]};
                // t_point p3 = {x, y + 1, fdf->z_values[y + 1][x]};
				p3.z *= Z_SCALE;
                p3.x *= SCALE; p3.y *= SCALE;
				isometric_projection(&p3.x, &p3.y, p3.z);
                p3.x += OFFSET_X; p3.y += OFFSET_Y;
                draw_line_dda(p1, p3, fdf);
            }
        }
    }
    mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
    mlx_hook(fdf->win_ptr, 17, 0, close_window, fdf);
    mlx_loop(fdf->mlx_ptr);
}
