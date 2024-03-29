/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:38:24 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/20 12:26:25 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_key_hook(t_data *mlx)
{
	int xo = 0;
	int yo = 0;
	if (mlx->key->a == 1)
	{
		mlx->map->pa += 8 * 0.8;
		mlx->map->pa = ft_fixang(mlx->map->pa);
		mlx->map->pdx = cos(degtorad(mlx->map->pa));
		mlx->map->pdy = -sin(degtorad(mlx->map->pa));
	}
	if (mlx->key->d == 1)
	{
		mlx->map->pa -= 8 * 0.8;
		mlx->map->pa = ft_fixang(mlx->map->pa);
		mlx->map->pdx = cos(degtorad(mlx->map->pa));
		mlx->map->pdy = -sin(degtorad(mlx->map->pa));
	}
	if (mlx->map->pdx < 0)
		xo = -20;
	else
		xo = 20;
	if (mlx->map->pdy < 0)
		yo = -20;
	else
		yo = 20;
	int ipx = mlx->map->px / 64.0, ipx_add_xo = (mlx->map->px + xo) / 64.0, ipx_sub_xo = (mlx->map->px - xo) / 64.0;
	int ipy = mlx->map->py / 64.0, ipy_add_yo = (mlx->map->py + yo) / 64.0, ipy_sub_yo = (mlx->map->py - yo) / 64.0;
	if (mlx->key->w == 1)
	{
		if (mlx->map->mapw[ipy * mlx->map->mapx + ipx_add_xo] == 0)
		{
			mlx->map->px += mlx->map->pdx * 7;
		}
		if (mlx->map->mapw[ipy_add_yo * mlx->map->mapx + ipx] == 0)
		{
			mlx->map->py += mlx->map->pdy * 7;
		}
		mlx->map->map[(int)mlx->map->py / 64][(int)mlx->map->px / 64] = 2;
	}
	if (mlx->key->s == 1)
	{
		if (mlx->map->mapw[ipy * mlx->map->mapx + ipx_sub_xo] == 0)
			mlx->map->px -= mlx->map->pdx * 7;
		if (mlx->map->mapw[ipy_sub_yo * mlx->map->mapx + ipx] == 0)
			mlx->map->py -= mlx->map->pdy * 7;
	}
}

int	ft_key_u(int key, t_data *mlx)
{
	if (key == 87)
	{
		mlx->map->ra_step -= 0.01;
		printf("ra_step = %f\n", mlx->map->ra_step);
	}
	if (key == A)
		mlx->key->a = 0;
	if (key == S)
		mlx->key->s = 0;
	if (key == D)
		mlx->key->d = 0;
	if (key == W)
		mlx->key->w = 0;
	return (0);
}

int	ft_key_d(int key, t_data *mlx)
{
	if (key == 86)
	{
		mlx->map->ra_step += 0.01;
		printf("ra_step = %f\n", mlx->map->ra_step);
	}
	if (key == A)
		mlx->key->a = 1;
	if (key == S)
		mlx->key->s = 1;
	if (key == D)
		mlx->key->d = 1;
	if (key == W)
		mlx->key->w = 1;
	if (key == ESC)
		ft_free(mlx);
	return (0);
}
