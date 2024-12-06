#include "../fdf.h"
#include <stdio.h>  // for printf

// Example debugging function to print the map dimensions and z_values
void debug_print_map_info(t_fdf *fdf)
{
    printf("Map Width: %d, Map Height: %d\n", fdf->map_width, fdf->map_height);
    for (int y = 0; y < fdf->map_height; y++)
    {
        for (int x = 0; x < fdf->map_width; x++)
        {
            printf("%d ", fdf->z_values[y][x]);
        }
        printf("\n");
    }
}

// Example debugging function to print coordinates before and after projection
void debug_print_point_transformations(int x, int y, int z)
{
    // int original_x = x;
    // int original_y = y;

    // Print the original coordinates
    printf("Original: (%d, %d, %d)\n", x, y, z);

    // Apply scaling first
    x *= SCALE;
    y *= SCALE;
    printf("After scaling: (%d, %d, %d)\n", x, y, z);

    // Uncomment this block to temporarily skip isometric projection
    // and see what happens if you just draw in plain 2D.
    //printf("(Skipping isometric projection)\n");

    // Apply isometric projection
    isometric_projection(&x, &y, z);
    printf("After isometric projection: (%d, %d, %d)\n", x, y, z);

    // Apply offsets
    x += OFFSET_X;
    y += OFFSET_Y;
    printf("After offsets: (%d, %d, %d)\n", x, y, z);

    printf("----\n");
}

// Use this debug version of the render function to inspect what’s going on
void debug_render(t_fdf *fdf)
{
    // Initialize MLX as usual
    fdf->mlx_ptr = mlx_init();
    if (!fdf->mlx_ptr)
    {
        ft_putstr_fd("Error: Failed to initialize MiniLibX.\n", 2);
        exit(EXIT_FAILURE);
    }

    fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 800, 600, "FdF Debug");
    if (!fdf->win_ptr)
    {
        ft_putstr_fd("Error: Failed to create a window.\n", 2);
        exit(EXIT_FAILURE);
    }

    fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, 800, 600);
    if (!fdf->img_ptr)
    {
        ft_putstr_fd("Error: Failed to create a new image.\n", 2);
        mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
        exit(EXIT_FAILURE);
    }

    fdf->img_data = mlx_get_data_addr(fdf->img_ptr,
                                      &fdf->bits_per_pixel,
                                      &fdf->line_length,
                                      &fdf->endian);
    if (!fdf->img_data)
    {
        ft_putstr_fd("Error: Failed to get image data address.\n", 2);
        mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
        mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
        exit(EXIT_FAILURE);
    }

    // Print map info for debugging
    debug_print_map_info(fdf);

    // For debugging, consider only drawing a small portion of the map, 
    // like the first few points
    int max_x = (fdf->map_width > 3) ? 3 : fdf->map_width;
    int max_y = (fdf->map_height > 3) ? 3 : fdf->map_height;

    for (int y = 0; y < max_y; y++)
    {
        for (int x = 0; x < max_x; x++)
        {
            t_point p1 = {x, y, fdf->z_values[y][x]};

            // Print transformation steps for this point
            debug_print_point_transformations(p1.x, p1.y, p1.z);

            // Apply the actual transformations for drawing
            int transformed_x = p1.x * SCALE;
            int transformed_y = p1.y * SCALE;
            isometric_projection(&transformed_x, &transformed_y, p1.z);
            transformed_x += OFFSET_X;
            transformed_y += OFFSET_Y;

            t_point p_proj1 = {transformed_x, transformed_y, p1.z};

            if (x < max_x - 1)
            {
                t_point p2 = {x + 1, y, fdf->z_values[y][x + 1]};
                int t2x = p2.x * SCALE;
                int t2y = p2.y * SCALE;
                isometric_projection(&t2x, &t2y, p2.z);
                t2x += OFFSET_X;
                t2y += OFFSET_Y;
                t_point p_proj2 = {t2x, t2y, p2.z};

                draw_line_dda(p_proj1, p_proj2, fdf);
            }

            if (y < max_y - 1)
            {
                t_point p3 = {x, y + 1, fdf->z_values[y + 1][x]};
                int t3x = p3.x * SCALE;
                int t3y = p3.y * SCALE;
                isometric_projection(&t3x, &t3y, p3.z);
                t3x += OFFSET_X;
                t3y += OFFSET_Y;
                t_point p_proj3 = {t3x, t3y, p3.z};

                draw_line_dda(p_proj1, p_proj3, fdf);
            }
        }
    }

    mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
    mlx_hook(fdf->win_ptr, 17, 0, close_window, fdf);
    mlx_loop(fdf->mlx_ptr);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_putstr_fd("Usage: ./fdf <map.fdf>\n", 2);
        return (EXIT_FAILURE);
    }

    t_fdf *fdf_data = init_fdf();
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

    // Use the debug_render instead of render to inspect your data and transformations
    debug_render(fdf_data);

    free_fdf(fdf_data);
    return (EXIT_SUCCESS);
}
