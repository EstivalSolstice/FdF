/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:53:48 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/06 20:50:56 by joltmann         ###   ########.fr       */
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
    return (fdf);
}

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

int parse_line(char *line, int *z_line, int *color_line, int width)
{
    char    **nums;
	int     i;
	char	*comma;

	i = 0;
    nums = ft_split(line, ' ');
    if (!nums)
        return (printf("Halloline 1"), 0);
    while (nums[i])
    {
		comma = ft_strchr(nums[i], ',');
        if (comma)
        {
            *comma = '\0';
            z_line[i] = ft_atoi(nums[i]);
            color_line[i] = strtol(comma + 1, NULL, 16);
        }
        else
        {
            z_line[i] = ft_atoi(nums[i]);
            // color_line[i] = 0xFFFFFF;
			color_line[i] = 0xFF00FF;
        }
        free(nums[i]);
		i++;
    }
    free(nums);
	printf("Parsed %d elements, expected width: %d\n", i, width);
	
	if (i != width)
    {
        printf("Line width mismatch: got %d, expected %d\n", i, width);
        return 0;
    }
	
    return (1);
}

int parse_map(const char *file_name, t_fdf *fdf)
{
    int     fd;
    char    *line;
    int     i;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (0);

    i = 0;
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
	fdf->colors = malloc(sizeof(int *) * fdf->map_height);
    fdf->z_values = malloc(sizeof(int *) * fdf->map_height);
    if (!fdf->z_values)
        return (0);
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (0);
    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
		fdf->colors[i] = malloc(sizeof(int) * fdf->map_width);
        fdf->z_values[i] = malloc(sizeof(int) * fdf->map_width);
        if (!fdf->z_values[i] || !parse_line(line, fdf->z_values[i], fdf->colors[i], fdf->map_width))
        {
            free(line);
            close(fd);
            return (printf("Hallo3"), 0);
        }
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
    render(fdf_data);
    free_fdf(fdf_data);
    return (EXIT_SUCCESS);
}
