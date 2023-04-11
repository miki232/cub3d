/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:38:24 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/09 15:13:01 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void    ft_key_hook(t_data *mlx)
{
    if (mlx->map->r == 120) /// da cambiare con mlx->map->a 
    {
        mlx->map->pa += 7 * 0.8;
        mlx->map->pa = ft_fixang(mlx->map->pa);
        mlx->map->pdx = cos(degtorad(mlx->map->pa));
        mlx->map->pdy = -sin(degtorad(mlx->map->pa));
    }
    if (mlx->key->d == 1)
    {
        mlx->map->pa -= 7 * 0.8;
        mlx->map->pa = ft_fixang(mlx->map->pa);
        mlx->map->pdx = cos(degtorad(mlx->map->pa));
        mlx->map->pdy = -sin(degtorad(mlx->map->pa));
    }
    int xo = 0;
    if (mlx->map->pdx < 0)
        xo = -20;
    else
        xo = 20;
    int yo = 0;
    if (mlx->map->pdy < 0)
        yo = -20;
    else
        yo = 20;
    int ipx = mlx->map->px / 64.0, ipx_add_xo = (mlx->map->px + xo) / 64.0, ipx_sub_xo = (mlx->map->px - xo) / 64.0;
    int ipy = mlx->map->py / 64.0, ipy_add_yo = (mlx->map->py + yo) / 64.0, ipy_sub_yo = (mlx->map->py - yo) / 64.0;
    if (mlx->key->w == 1)
    {
        if (mlx->map->mapw[ipy * mlx->map->mapx + ipx_add_xo] == 0)
            mlx->map->px += mlx->map->pdx * 6;
        if (mlx->map->mapw[ipy_add_yo * mlx->map->mapx + ipx] == 0)
            mlx->map->py += mlx->map->pdy * 6;
    }
    if (mlx->key->s == 1)
    {
        if (mlx->map->mapw[ipy * mlx->map->mapx + ipx_sub_xo] == 0)
            mlx->map->px -= mlx->map->pdx * 6;
        if (mlx->map->mapw[ipy_sub_yo * mlx->map->mapx + ipx] == 0)
            mlx->map->py -= mlx->map->pdy * 6;
    }
}


int	ft_key_u(int key, t_data *mlx)
{
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
	if (key == A)
        mlx->key->a = 1;
    if (key == S)
        mlx->key->s = 1;
    if (key == D)
        mlx->key->d = 1;
    if (key == W)
        mlx->key->w = 1;
    if (key == ESC)
        exit(0);
    return (0);
}