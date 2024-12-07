/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:24:56 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 11:36:36 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_map_dimensions(const char *file_name, t_map_data *map)
{
	int		fd;
	char	*line;
	int		rows;
	int		max_width;
	int		width;

	rows = 0;
	max_width = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		width = ft_count_words(line, ' ');
		if (width > max_width)
			max_width = width;
		rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (rows == 0 || max_width == 0)
		return (0);
	return (map->width = max_width, map->height = rows, 1);
}

int	allocate_map_data(t_map_data *map)
{
	map->row_widths = malloc(sizeof(int) * map->height);
	map->z_values = malloc(sizeof(int *) * map->height);
	map->colors = malloc(sizeof(int *) * map->height);
	if (!map->row_widths || !map->z_values || !map->colors)
	{
		free(map->row_widths);
		free(map->z_values);
		free(map->colors);
		return (0);
	}
	return (1);
}

int	parse_row(char *line, int row, t_map_data *map)
{
	int			width;
	t_row_data	row_data;

	width = ft_count_words(line, ' ');
	map->row_widths[row] = width;
	map->z_values[row] = malloc(sizeof(int) * width);
	map->colors[row] = malloc(sizeof(int) * width);
	if (!map->z_values[row] || !map->colors[row])
	{
		free(map->z_values[row]);
		free(map->colors[row]);
		return (0);
	}
	row_data.z_line = map->z_values[row];
	row_data.color_line = map->colors[row];
	row_data.actual_width = &map->row_widths[row];
	if (!parse_line(line, &row_data, width))
	{
		free(map->z_values[row]);
		free(map->colors[row]);
		return (0);
	}
	return (1);
}

void	update_min_max_z(t_map_data *map, int row)
{
	int	col;

	col = 0;
	while (col < map->row_widths[row])
	{
		if (map->z_values[row][col] < map->min_z)
			map->min_z = map->z_values[row][col];
		if (map->z_values[row][col] > map->max_z)
			map->max_z = map->z_values[row][col];
		col++;
	}
}

int	parse_map(const char *file_name, t_map_data *map)
{
	int		fd;
	char	*line;
	int		row;

	row = 0;
	if (!parse_map_dimensions(file_name, map))
		return (0);
	if (!allocate_map_data(map))
		return (0);
	map->min_z = INT_MAX;
	map->max_z = INT_MIN;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!parse_row(line, row, map))
			return (free(line), close(fd), 0);
		update_min_max_z(map, row);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	return (close(fd), 1);
}
