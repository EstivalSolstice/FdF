/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:53:48 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 06:22:16 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*initialize_fdf(void)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->map.width = 0;
	fdf->map.height = 0;
	fdf->map.z_values = NULL;
	fdf->map.colors = NULL;
	fdf->map.row_widths = NULL;
	fdf->cam.x = 0;
	fdf->cam.y = 0;
	fdf->cam.z = 0;
	fdf->cam.rotation_x = 0.0;
	fdf->cam.rotation_y = 0.0;
	fdf->cam.scale = 1.0;
	fdf->render.mlx_ptr = NULL;
	fdf->render.win_ptr = NULL;
	fdf->render.img.ptr = NULL;
	fdf->render.img.data = NULL;
	return (fdf);
}

void	free_fdf(t_fdf *fdf)
{
	int	i;

	if (fdf->map.z_values || fdf->map.colors)
	{
		i = 0;
		while (i < fdf->map.height)
		{
			if (fdf->map.z_values)
				free(fdf->map.z_values[i]);
			if (fdf->map.colors)
				free(fdf->map.colors[i]);
			i++;
		}
	}
	free(fdf->map.z_values);
	free(fdf->map.colors);
	free(fdf->map.row_widths);
	if (fdf->render.img.ptr && fdf->render.mlx_ptr)
		mlx_destroy_image(fdf->render.mlx_ptr, fdf->render.img.ptr);
	if (fdf->render.win_ptr && fdf->render.mlx_ptr)
		mlx_destroy_window(fdf->render.mlx_ptr, fdf->render.win_ptr);
	free(fdf);
}

int	ft_count_words(char *line, char delimiter)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == delimiter && line[i] != '\0')
			i++;
		if (line[i] != delimiter && line[i] != '\0')
			count++;
		while (line[i] != delimiter && line[i] != '\0')
			i++;
	}
	return (count);
}

int	parse_hex(const char *str)
{
	int	result;

	result = 0;
	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	else if (*str == '#')
		str++;
	while (*str)
	{
		result *= 16;
		if (*str >= '0' && *str <= '9')
			result += *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			result += *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			result += *str - 'A' + 10;
		else
			return (0);
		str++;
	}
	return (result);
}

int	parse_line(char *line, t_row_data *row_data, int width)
{
	char	**nums;
	char	*comma;
	int		i;

	i = 0;
	nums = ft_split(line, ' ');
	if (!nums)
		return (printf("Error: ft_split failed\n"), 0);
	while (nums[i])
	{
		comma = ft_strchr(nums[i], ',');
		row_data->z_line[i] = ft_atoi(nums[i]);
		if (comma)
		{
			*comma = '\0';
			row_data->color_line[i] = parse_hex(comma + 1);
		}
		else
			row_data->color_line[i] = 0xFF00FF;
		free(nums[i]);
		i++;
	}
	if (i != width)
		return (printf("Error: Invalid row width\n"), free(nums), 0);
	return (free(nums), *(row_data->actual_width) = i, 1);
}

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
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!parse_row(line, row, map))
			return (free(line), close(fd), 0);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf_data;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf <map.fdf>\n", 2);
		return (EXIT_FAILURE);
	}
	fdf_data = initialize_fdf();
	if (!fdf_data)
	{
		ft_putstr_fd("Error: Failed to initialize fdf structure.\n", 2);
		return (EXIT_FAILURE);
	}
	if (!parse_map(argv[1], &fdf_data->map))
	{
		ft_putstr_fd("Error: Failed to parse the map.\n", 2);
		free_fdf(fdf_data);
		return (EXIT_FAILURE);
	}
	validate_input(fdf_data);
	mlx_hook(fdf_data->render.win_ptr, 17, 0, close_window, fdf_data);
	mlx_hook(fdf_data->render.win_ptr, 2, 1L << 0, key_hook, fdf_data);
	mlx_loop(fdf_data->render.mlx_ptr);
	free_fdf(fdf_data);
	return (EXIT_SUCCESS);
}
