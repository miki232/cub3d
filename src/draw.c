/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:54 by mtoia             #+#    #+#             */
/*   Updated: 2023/05/01 15:50:54 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;
	
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear(t_data *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img->img);
	mlx->img->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img->bits_per_pixel, \
		&mlx->img->line_length, &mlx->img->endian);
	mlx_destroy_image(mlx->mlx_ptr, mlx->imgmlt->img);
	mlx->imgmlt->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->imgmlt->addr = mlx_get_data_addr(mlx->imgmlt->img, &mlx->imgmlt->bits_per_pixel, \
		&mlx->imgmlt->line_length, &mlx->imgmlt->endian);
}
