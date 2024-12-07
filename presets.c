/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:27:54 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 11:28:22 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_preset_views(int keycode, t_camera *cam, t_map_data *map)
{
	t_camera	preset;
	int			map_center_x;
	int			map_center_y;
	int			map_center_z;

	map_center_x = cam->scale * (map->width - 1) / 2;
	map_center_y = cam->scale * (map->height - 1) / 2;
	map_center_z = cam->scale * (map->max_z - map->min_z) / 2;
	if (keycode == 18)
		preset = (t_camera){map_center_x, -map->height * cam->scale,
			map_center_z, -90.0, 0.0, 1.0};
	else if (keycode == 19)
		preset = (t_camera){map_center_x, map_center_y, map->width * cam->scale,
			0.0, 90.0, 1.0};
	else if (keycode == 20)
		preset = (t_camera){map_center_x, map_center_y, map->height
			* cam->scale, 0.0, 0.0, 1.0};
	else if (keycode == 21)
		preset = (t_camera){map_center_x, map_center_y, map->width * cam->scale,
			0.0, 0.0, 1.0};
	else
		return ;
	apply_camera_preset(cam, preset);
}
