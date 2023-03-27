/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:18:20 by mtoia             #+#    #+#             */
/*   Updated: 2023/03/27 17:11:25 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_create_level(t_data *mlx)
{
    int		i;
    int		x;
    int		y;

    i = 0;
    x = 0;
    y = 0;
    while (mlx->map->map[i] != '\0')
    {
        if (mlx->map->map[i] == '1')
        {
            mlx->img = mlx_new_image(mlx->mlx_ptr, 10, 10);
            mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
            ft_square(mlx, 0xFFFF00);
            mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, x, y);
            x += 10;       
        }
        else if (mlx->map->map[i] == '0')
        {
            x += 10;
        }
        else if (mlx->map->map[i] == '\n')
        {
            x = 0;
            y += 10;
        }
        else if (mlx->map->map[i] == 'N')
        {
            mlx->map->player_y = y;
            mlx->map->player_x = x;
            x += 10;
        }
        i++;
    }
}