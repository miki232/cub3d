/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daw.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:54 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/03 17:12:03 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	clear(t_data *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->addr =	mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}

void	verline(t_data *mlx, int x, int y1, int y2, int color)
{
	while (y1 <= y2)
	{
		my_mlx_pixel_put(mlx, x, y1, color);
		y1++;
	}
}