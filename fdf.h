/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:53:59 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 11:30:43 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "minilbx_opengl_20191021/mlx.h"
# include "libft/libft.h"

# define Z_SCALE 5
# define OFFSET_X 600
# define OFFSET_Y 400

# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_A 0
# define KEY_D 2
# define KEY_W 13
# define KEY_S 1
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define PLUS 24
# define MINUS 27
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_dda
{
	int		steps;
	float	x;
	float	y;
	float	x_inc;
	float	y_inc;
	float	color;
	float	color_inc;
}	t_dda;

typedef struct s_row_data
{
	int	*z_line;
	int	*color_line;
	int	*actual_width;
}	t_row_data;

typedef struct s_map_data
{
	int		width;
	int		height;
	int		**z_values;
	int		**colors;
	int		*row_widths;
	int		min_z;
	int		max_z;
}	t_map_data;

typedef struct s_camera
{
	int		x;
	int		y;
	int		z;
	float	rotation_x;
	float	rotation_y;
	float	scale;
}	t_camera;

typedef struct s_image
{
	void	*ptr;
	char	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_render_context
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
}	t_render_context;

typedef struct s_fdf
{
	t_map_data			map;
	t_camera			cam;
	t_render_context	render;
}	t_fdf;

// camera.c
void	apply_camera(t_point *point, t_camera *cam);
void	apply_camera_preset(t_camera *cam, t_camera preset);
void	handle_camera_movement(int keycode, t_camera *cam);
void	handle_camera_rotation(int keycode, t_camera *cam);
void	handle_zoom(int keycode, t_camera *cam);

// projection.c
void	apply_rotation(t_point *point, t_camera *cam);
void	isometric_projection(t_point *point);
void	transform_and_project(t_fdf *fdf, t_point *point);
t_point	transform_point(t_fdf *fdf, t_point input);

// render.c
void	render_map(t_fdf *fdf);
void	redraw(t_fdf *fdf);
void	draw_horizontal_line(t_fdf *fdf, t_point p1, int x, int y);
void	draw_vertical_line(t_fdf *fdf, t_point p1, int x, int y);
void	process_row(t_fdf *fdf, t_map_data *map, int y);

// draw.c
void	put_pixel_to_image(t_fdf *fdf, int x, int y, int color);
void	draw_line_dda(t_point p1, t_point p2, t_fdf *fdf);

// input.c
int		key_hook(int keycode, t_fdf *fdf);
void	validate_input(t_fdf *fdf);
int		close_window(t_fdf *fdf);

// map.c
int		parse_map_dimensions(const char *file_name, t_map_data *map);
int		allocate_map_data(t_map_data *map);
int		parse_row(char *line, int row, t_map_data *map);
void	update_min_max_z(t_map_data *map, int row);
int		parse_map(const char *file_name, t_map_data *map);

// parse_utils.c
int		ft_count_words(char *line, char delimiter);
int		parse_hex(const char *str);
int		parse_line(char *line, t_row_data *row_data, int width);

// init.c
t_fdf	*initialize_fdf(void);
void	free_fdf(t_fdf *fdf);

// preset_views.c
void	handle_preset_views(int keycode, t_camera *cam, t_map_data *map);

#endif