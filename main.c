/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:53:48 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 11:36:28 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
