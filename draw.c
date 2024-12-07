/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:58:56 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/07 11:40:13 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_to_image(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 1200 && y >= 0 && y < 800)
	{
		dst = fdf->render.img.data + (y * fdf->render.img.line_length
				+ x * (fdf->render.img.bits_per_pixel / 8));
		*(unsigned int *)dst = (unsigned int)color;
	}
}

void	draw_line_dda(t_point p1, t_point p2, t_fdf *fdf)
{
	t_dda	dda;
	int		i;

	dda.steps = (int)fmax(abs(p2.x - p1.x), abs(p2.y - p1.y));
	dda.x = p1.x;
	dda.y = p1.y;
	dda.x_inc = (float)(p2.x - p1.x) / dda.steps;
	dda.y_inc = (float)(p2.y - p1.y) / dda.steps;
	dda.color = p1.color;
	dda.color_inc = (float)(p2.color - p1.color) / dda.steps;
	i = 0;
	while (i <= dda.steps)
	{
		put_pixel_to_image(fdf, (int)roundf(dda.x), (int)roundf(dda.y),
			(int)dda.color);
		dda.x += dda.x_inc;
		dda.y += dda.y_inc;
		dda.color += dda.color_inc;
		i++;
	}
}
