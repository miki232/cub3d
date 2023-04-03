/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:18:20 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/03 19:02:07 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_get_player_pos(t_data *mlx)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (mlx->map->map[i])
	{
		if (mlx->map->map[i] == '\n')
		{
			x = 0;
			y+= 33;
		}
		else if (mlx->map->map[i] == ' ' || mlx->map->map[i] == '1' || mlx->map->map[i] == '0')
		{
			x+= 33;
		}
		if (mlx->map->map[i] == 'N')
		{
			mlx->map->player_x = x;
			mlx->map->player_y = y;
		}
		i++;
	}
	printf("player_x = %d\n", mlx->map->player_x);
	printf("player_y = %d\n", mlx->map->player_y);
}

int	ft_key(int key, t_data *mlx)
{
	if (key == 123) //sinistra
	{
		mlx->map->pa -= 0.1;
		if (mlx->map->pa < 0)
			mlx->map->pa += 2 * PI;
		mlx->map->pdx = cos(mlx->map->pa) * 5;
		mlx->map->pdy = sin(mlx->map->pa) * 5;
	}
	if (key == 124) //destra
	{
		mlx->map->pa += 0.1;
		if (mlx->map->pa > 2 * PI)
			mlx->map->pa -= 2 * PI;
		mlx->map->pdx = cos(mlx->map->pa) * 5;
		mlx->map->pdy = sin(mlx->map->pa) * 5;
	}
	if (key == 125) //giu
	{
		mlx->map->player_y -= mlx->map->pdy;
		mlx->map->player_x -= mlx->map->pdx;
	}
	if (key == 126) //su
	{
		mlx->map->player_y += mlx->map->pdy;
		mlx->map->player_x += mlx->map->pdx;
	}
	return (0);
}


int ft_draw(t_data *mlx)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	clear(mlx);
	while (mlx->map->map[i])
	{
		if (mlx->map->map[i] == '1')
			ft_square(mlx, x, y, 0x00FF0000);
		else if (mlx->map->map[i] == '0')
			ft_square(mlx, x, y, 0x00000FF0);
		else if (mlx->map->map[i] == 'N')
		{
			ft_square(mlx, x, y, 0x00000FF0);
			
		}
		if (mlx->map->map[i] == '\n')
		{
			x = 0;
			y += 33;
		}
		else
			x += 33;
		i++;
	}
	// ft_player(mlx, mlx->map->player_x, mlx->map->player_y, 0xFFFFFF);
	drawline(mlx->map->player_x, mlx->map->player_y, mlx->map->player_x + mlx->map->pdx, mlx->map->player_y + mlx->map->pdy, mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	return (0);
}

void	ft_create_level(t_data *mlx)
{
	ft_get_player_pos(mlx);
	mlx->map->pdx = cos(mlx->map->pa) * 5;
	mlx->map->pdy = sin(mlx->map->pa) * 5;
	mlx_loop_hook(mlx->mlx_ptr, ft_draw, mlx);
	mlx_hook(mlx->win_ptr, 2, (1L << 0), ft_key, mlx);

	// ft_square(mlx, 0, 0, 0x00FF0000);
	printf("player found at x: %d y: %d\n", mlx->map->player_x, mlx->map->player_y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}