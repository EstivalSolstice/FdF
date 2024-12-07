/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:23:43 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 11:40:16 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_camera(t_point *point, t_camera *cam)
{
	point->x -= cam->x;
	point->y -= cam->y;
	point->z -= cam->z;
}

void	apply_camera_preset(t_camera *cam, t_camera preset)
{
	cam->x = preset.x;
	cam->y = preset.y;
	cam->z = preset.z;
	cam->rotation_x = preset.rotation_x;
	cam->rotation_y = preset.rotation_y;
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

void	handle_zoom(int keycode, t_camera *cam)
{
	if (keycode == 24)
		cam->scale += 0.1;
	else if (keycode == 27)
		cam->scale -= 0.1;
}
