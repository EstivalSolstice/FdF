/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:58:56 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 02:26:40 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void apply_camera(t_point *point, t_fdf *fdf)
{
    point->x -= fdf->camera_x;
    point->y -= fdf->camera_y;
    point->z -= fdf->camera_z;
}

void apply_rotation(t_point *point, t_fdf *fdf)
{
	float	rad_x;
    float	rad_y;
    int		x;
	int		y;
    int		z;

	rad_x = fdf->rotation_angle_x * (M_PI / 180.0);
	rad_y = fdf->rotation_angle_y * (M_PI / 180.0);
	x = point->x;
	y = point->y;
	z = point->z;
    point->x = (int)(x * cos(rad_y) + z * sin(rad_y));
    point->z = (int)(-x * sin(rad_y) + z * cos(rad_y));
    point->y = (int)(y * cos(rad_x) - z * sin(rad_x));
    point->z = (int)(y * sin(rad_x) + z * cos(rad_x));
}

void isometric_projection(t_point *point)
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

void transform_and_project(t_fdf *fdf, t_point *point)
{
    apply_camera(point, fdf);
    apply_rotation(point, fdf);
    isometric_projection(point);
}


void render_map(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
    mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);

    fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, 1200, 800);
    fdf->img_data = mlx_get_data_addr(fdf->img_ptr, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);

    for (int y = 0; y < fdf->map_height; y++)
    {
        for (int x = 0; x < fdf->row_widths[y]; x++)
        {
            t_point p1 = {x, y, fdf->z_values[y][x], fdf->colors[y][x]};
            p1.z *= Z_SCALE;
            p1.x *= fdf->scale;
            p1.y *= fdf->scale;
			apply_camera(&p1, fdf);
            apply_rotation(&p1, fdf);
            isometric_projection(&p1);
            p1.x += OFFSET_X;
            p1.y += OFFSET_Y;

            if (x < fdf->row_widths[y] - 1)
            {
                t_point p2 = {x + 1, y, fdf->z_values[y][x + 1], fdf->colors[y][x + 1]};
                p2.z *= Z_SCALE;
                p2.x *= fdf->scale;
                p2.y *= fdf->scale;
                apply_camera(&p2, fdf);
            	apply_rotation(&p2, fdf);
            	isometric_projection(&p2);
				p2.x += OFFSET_X;
                p2.y += OFFSET_Y;
                draw_line_dda(p1, p2, fdf);
            }

            if (y < fdf->map_height - 1 && x < fdf->row_widths[y + 1])
            {
                t_point p3 = {x, y + 1, fdf->z_values[y + 1][x], fdf->colors[y + 1][x]};
                p3.z *= Z_SCALE;
                p3.x *= fdf->scale;
                p3.y *= fdf->scale;
                apply_camera(&p3, fdf);
            	apply_rotation(&p3, fdf);
            	isometric_projection(&p3);
				p3.x += OFFSET_X;
                p3.y += OFFSET_Y;
                draw_line_dda(p1, p3, fdf);
            }
        }
    }
}


int key_hook(int keycode, t_fdf *fdf)
{
    if (keycode == 53) // ESC key
    {
        free_fdf(fdf);
        exit(0);
    }
	

    else if (keycode == 123) // Left arrow
        fdf->rotation_angle_y -= 5.0;
    else if (keycode == 124) // Right arrow
        fdf->rotation_angle_y += 5.0;
	else if (keycode == 126) // Up arrow
        fdf->rotation_angle_x -= 5.0;
    else if (keycode == 125) // Down arrow
        fdf->rotation_angle_x += 5.0;


    else if (keycode == 0) // A key
        fdf->camera_x += 10;
    else if (keycode == 2) // D key
        fdf->camera_x -= 10;
    else if (keycode == 13) // W key
        fdf->camera_y += 10;
    else if (keycode == 1) // S key
        fdf->camera_y -= 10;
		
		
	else if (keycode == 34) // I key
		fdf->camera_z -= 10;
	else if (keycode == 38) // J key
	{
		fdf->camera_x += 10;
		fdf->camera_y -= 10;
	}
	else if (keycode == 40) // K key
		fdf->camera_z += 10;
	else if (keycode == 37) // L key
	{
		fdf->camera_x -= 10;
		fdf->camera_y += 10;
	}	
	
	
	else if (keycode == 18) // 1 key: Reset camera to top view
	{
    	fdf->camera_x = 0;
    	fdf->camera_y = -500; // Move high above the scene
    	fdf->camera_z = 500;  // Keep some distance for a better view
	}
	else if (keycode == 19) // 2 key: Side view
	{
    	fdf->camera_x = 500;  // Move to the side
    	fdf->camera_y = 0;
    	fdf->camera_z = 500;  // Keep distance
	}
	else if (keycode == 20) // 3 key: Front view
	{
    	fdf->camera_x = 0;
    	fdf->camera_y = 0;
    	fdf->camera_z = 1000; // Move far back for a full view
	}
	else if (keycode == 21) // 4 key: Reset rotation angles
	{
		fdf->rotation_angle_x = 0.0;
		fdf->rotation_angle_y = 0.0;
	}
	
	
	else if (keycode == 24) // + key: Zoom in
    	fdf->scale += 0.1;
	else if (keycode == 27) // - key: Zoom out
    	fdf->scale -= 0.1;


	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
    mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
    fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, 1200, 800);
    fdf->img_data = mlx_get_data_addr(fdf->img_ptr, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
    render_map(fdf);
    mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
    return (0);
}

void validate_input(t_fdf *fdf)
{
    fdf->mlx_ptr = mlx_init();
    if (!fdf->mlx_ptr)
    {
        ft_putstr_fd("Error: Failed to initialize MiniLibX.\n", 2);
        exit(EXIT_FAILURE);
    }
    fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1200, 800, "FdF");
    if (!fdf->win_ptr)
    {
        ft_putstr_fd("Error: Failed to create a window.\n", 2);
        exit(EXIT_FAILURE);
    }
    fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, 1200, 800);
    if (!fdf->img_ptr)
    {
        ft_putstr_fd("Error: Failed to create a new image.\n", 2);
        mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
        exit(EXIT_FAILURE);
    }
    fdf->img_data = mlx_get_data_addr(fdf->img_ptr, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
	render_map(fdf);
    mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}

void put_pixel_to_image(t_fdf *fdf, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < 1200 && y >= 0 && y < 800)
    {
        dst = fdf->img_data + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
        *(unsigned int *)dst = (unsigned int)color;
    }
}

void draw_line_dda(t_point p1, t_point p2, t_fdf *fdf)
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
        put_pixel_to_image(fdf, (int)roundf(dda.x), (int)roundf(dda.y), (int)dda.color);
        dda.x += dda.x_inc;
        dda.y += dda.y_inc;
        dda.color += dda.color_inc;
        i++;
    }
}

int close_window(t_fdf *fdf)
{
    mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
    exit(0);
    return (0);
}
