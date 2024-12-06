/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:53:59 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/06 20:37:55 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "minilbx_opengl_20191021/mlx.h"
# include "libft/libft.h"

#define SCALE 1
#define Z_SCALE 1
#define OFFSET_X 440
#define OFFSET_Y 130

typedef struct s_point
{
    int x;
    int y;
    int z;
	int color;
}   t_point;

typedef struct s_fdf
{
    int     map_width;
    int     map_height;
    int     **z_values;
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
	int     **colors;
}   t_fdf;

void 	isometric_projection(int *x, int *y, int z);
void 	draw_line_dda(t_point p1, t_point p2, t_fdf *fdf);
void 	put_pixel_to_image(t_fdf *fdf, int x, int y, int color);
int		close_window(t_fdf *fdf);
void 	render(t_fdf *fdf);

int 	ft_count_words(char *line, char delimiter);
int		parse_line(char *line, int *z_line, int *color_line, int width);
int 	parse_map(const char *file_name, t_fdf *fdf);

t_fdf 	*init_fdf(void);
void 	free_fdf(t_fdf *fdf);

#endif