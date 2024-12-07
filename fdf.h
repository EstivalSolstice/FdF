/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:53:59 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 02:33:17 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "minilbx_opengl_20191021/mlx.h"
# include "libft/libft.h"

// #define SCALE 3
#define Z_SCALE 3.5
#define OFFSET_X 600
#define OFFSET_Y 400

#define KEY_ESC 53
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_A 0
#define KEY_D 2
#define KEY_W 13
#define KEY_S 1
#define KEY_1 18
#define KEY_2 19
#define KEY_3 20
#define KEY_4 21
#define PlUS 24
#define MINUS 27
#define KEY_I 34
#define KEY_J 38
#define KEY_K 40
#define KEY_L 37

typedef struct s_point
{
    int x;
    int y;
    int z;
	int color;
}   t_point;

typedef struct s_dda
{
    int     steps;
    float   x;
    float   y;
    float   x_inc;
    float   y_inc;
    float   color;
    float   color_inc;
}   t_dda;

typedef struct s_fdf
{
    int     map_width;
    int     map_height;
	int	    *row_widths;
    int     **z_values;
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
	int     **colors;
	float   rotation_angle_x;
	float   rotation_angle_y;
	int		camera_x;
    int 	camera_y;
    int 	camera_z;
	float   scale;
}   t_fdf;

// typedef struct s_map_data
// {
//     int     width;          // Map width
//     int     height;         // Map height
//     int     **z_values;     // 2D array of z-values
//     int     **colors;       // 2D array of colors
//     int     *row_widths;    // Row-specific widths
// }   t_map_data;

// typedef struct s_camera
// {
//     int     x;              // Camera x position
//     int     y;              // Camera y position
//     int     z;              // Camera z position
//     float   rotation_x;     // Rotation angle around x-axis
//     float   rotation_y;     // Rotation angle around y-axis
//     float   scale;          // Scaling factor
// }   t_camera;

// typedef struct s_image
// {
//     void    *ptr;           // MiniLibX image pointer
//     char    *data;          // Image data (pixel buffer)
//     int     bits_per_pixel; // Bits per pixel
//     int     line_length;    // Bytes per row
//     int     endian;         // Endianness
// }   t_image;

// typedef struct s_render_context
// {
//     void    *mlx_ptr;       // MiniLibX instance pointer
//     void    *win_ptr;       // MiniLibX window pointer
//     t_image img;            // Image data
// }   t_render_context;

// typedef struct s_fdf
// {
//     t_map_data       map;   // Map data
//     t_camera         cam;   // Camera settings
//     t_render_context render; // Rendering context
// }   t_fdf;

void	apply_camera(t_point *point, t_fdf *fdf);
void	apply_rotation(t_point *point, t_fdf *fdf);
void	isometric_projection(t_point *point);
void	transform_and_project(t_fdf *fdf, t_point *point);

void	render_map(t_fdf *fdf);
int     key_hook(int keycode, t_fdf *fdf);

void 	put_pixel_to_image(t_fdf *fdf, int x, int y, int color);
void	validate_input(t_fdf *fdf);

void 	draw_line_dda(t_point p1, t_point p2, t_fdf *fdf);
int		close_window(t_fdf *fdf);

int		parse_hex(const char *str);
int		parse_line(char *line, int *z_line, int *color_line, int width, int *actual_width);
int 	parse_map(const char *file_name, t_fdf *fdf);

t_fdf 	*init_fdf(void);
void 	free_fdf(t_fdf *fdf);

int 	ft_count_words(char *line, char delimiter);

#endif