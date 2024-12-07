/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:53:48 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 02:33:42 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf *init_fdf(void)
{
    t_fdf *fdf = malloc(sizeof(t_fdf));
    if (!fdf)
        return (NULL);

    fdf->mlx_ptr = NULL;
    fdf->win_ptr = NULL;
    fdf->img_ptr = NULL;
    fdf->img_data = NULL;
    fdf->z_values = NULL;
    fdf->map_width = 0;
    fdf->map_height = 0;
    fdf->bits_per_pixel = 0;
    fdf->line_length = 0;
    fdf->endian = 0;
	fdf->colors = NULL;
	fdf->row_widths = NULL;
	fdf->rotation_angle_x = 0.0;
	fdf->rotation_angle_y = 0.0;
	fdf->camera_x = 0;
	fdf->camera_y = 0;
	fdf->camera_z = 0;	
	fdf->scale = 1.0;
    return (fdf);
}

// void initialize_fdf(t_fdf *fdf)
// {
//     fdf->map.width = 0;
//     fdf->map.height = 0;
//     fdf->map.z_values = NULL;
//     fdf->map.colors = NULL;
//     fdf->map.row_widths = NULL;

//     fdf->cam.x = 0;
//     fdf->cam.y = 0;
//     fdf->cam.z = 0;
//     fdf->cam.rotation_x = 0.0;
//     fdf->cam.rotation_y = 0.0;
//     fdf->cam.scale = 1.0;

//     fdf->render.mlx_ptr = mlx_init();
//     fdf->render.win_ptr = NULL;
//     fdf->render.img.ptr = NULL;
// }

void free_fdf(t_fdf *fdf)
{
    int i;

    if (fdf->z_values)
    {
        for (i = 0; i < fdf->map_height; i++)
            free(fdf->z_values[i]);
        free(fdf->z_values);
    }
    if (fdf->img_ptr && fdf->mlx_ptr)
        mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
    if (fdf->win_ptr && fdf->mlx_ptr)
        mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
    free(fdf);
}

int ft_count_words(char *line, char delimiter)
{
    int count = 0;
    int i = 0;

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

int parse_hex(const char *str)
{
    int result;
	
	result = 0;
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

int parse_line(char *line, int *z_line, int *color_line, int width, int *actual_width)
{
    char    **nums;
	char	*comma;
	int     i;

	i = 0;
    nums = ft_split(line, ' ');
	if (!nums)
        return (printf("Error: ft_split failed\n"), 0);
    while (nums[i])
    {
		comma = ft_strchr(nums[i], ',');
        if (comma)
        {
            *comma = '\0';
            z_line[i] = ft_atoi(nums[i]);
            color_line[i] = parse_hex(comma + 1);
        }
        else
        {
            z_line[i] = ft_atoi(nums[i]);
			color_line[i] = 0xFF00FF;
        }
        free(nums[i]);
		i++;
    }
    free(nums);
	*actual_width = i;
    return (1);
}

int parse_map(const char *file_name, t_fdf *fdf)
{
    int     fd;
    char    *line;
    int     i;
	int     actual_width;

	i = 0;
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (0);
    while ((line = get_next_line(fd)) != NULL)
    {
        if (i == 0)
            fdf->map_width = ft_count_words(line, ' ');
        free(line);
        i++;
    }
    close(fd);
    fdf->map_height = i;
    if (fdf->map_height == 0 || fdf->map_width == 0)
        return (0);
	
	fdf->row_widths = malloc(sizeof(int) * fdf->map_height);
	if (!fdf->row_widths)
    	return (0);
	fdf->colors = malloc(sizeof(int *) * fdf->map_height);
	if (!fdf->colors)
		return (0);
    fdf->z_values = malloc(sizeof(int *) * fdf->map_height);
    if (!fdf->z_values)
        return (0);
	
	
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (0);
		

    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
		actual_width = ft_count_words(line, ' ');
        fdf->row_widths[i] = actual_width;
		
		fdf->colors[i] = malloc(sizeof(int) * actual_width);
        fdf->z_values[i] = malloc(sizeof(int) * actual_width);
		if (!fdf->colors[i] || !fdf->z_values[i] || !parse_line(line, fdf->z_values[i], fdf->colors[i], actual_width, &fdf->row_widths[i]))
        {
            free(line);
            close(fd);
            return (printf("Error: Failed to parse row %d.\n", i), 0);
        }

        if (actual_width > fdf->map_width)
            fdf->map_width = actual_width;
        free(line);
        i++;
    }
    close(fd);
    return (1);
}

int main(int argc, char **argv)
{
    t_fdf *fdf_data;

    if (argc != 2)
    {
        ft_putstr_fd("Usage: ./fdf <map.fdf>\n", 2);
        return (EXIT_FAILURE);
    }
    fdf_data = init_fdf();
    if (!fdf_data)
    {
        ft_putstr_fd("Error: Failed to initialize fdf structure.\n", 2);
        return (EXIT_FAILURE);
    }
    if (!parse_map(argv[1], fdf_data))
    {
        ft_putstr_fd("Error: Failed to parse the map.\n", 2);
        free_fdf(fdf_data);
        return (EXIT_FAILURE);
    }
    validate_input(fdf_data);
	mlx_hook(fdf_data->win_ptr, 17, 0, close_window, fdf_data);
    mlx_hook(fdf_data->win_ptr, 2, 1L << 0, key_hook, fdf_data);
    mlx_loop(fdf_data->mlx_ptr);
    free_fdf(fdf_data);
    return (EXIT_SUCCESS);
}
