/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:24:14 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 11:39:06 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
