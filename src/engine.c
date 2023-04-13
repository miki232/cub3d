/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:18:20 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/13 15:20:05 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
# include "../src/All_Textures.ppm"

void	ft_vert_line(t_data *mlx)
{
	mlx->map->dof = 0;
	mlx->map->disv = 1000000000;
	mlx->map->tan = tan(degtorad(mlx->map->ra));
	if (cos(degtorad(mlx->map->ra)) > 0.001)
	{
		mlx->map->rx = (((int)mlx->map->px >> 6) << 6) + 64;
		mlx->map->ry = (mlx->map->px - mlx->map->rx) * mlx->map->tan + mlx->map->py;
		mlx->map->xo = 64;
		mlx->map->yo = -mlx->map->xo * mlx->map->tan;
	}
	else if (cos(degtorad(mlx->map->ra)) < -0.001)
	{
		mlx->map->rx = (((int)mlx->map->px >> 6) << 6) -0.001;
		mlx->map->ry = (mlx->map->px - mlx->map->rx) * mlx->map->tan + mlx->map->py;
		mlx->map->xo = -64;
		mlx->map->yo = -mlx->map->xo * mlx->map->tan;
	}
	else
	{
		mlx->map->rx = mlx->map->px;
		mlx->map->ry = mlx->map->py;
		mlx->map->dof = 15;
	}
	while (mlx->map->dof < 15)
	{
		mlx->map->mx = (int)(mlx->map->rx) >> 6;
		mlx->map->my = (int)(mlx->map->ry) >> 6;
		mlx->map->mp = mlx->map->my * mlx->map->mapx + mlx->map->mx;
		if (mlx->map->mp > 0 && mlx->map->mp < mlx->map->mapx * mlx->map->mapy && mlx->map->mapw[mlx->map->mp] > 0)
		{
			mlx->map->vmt = mlx->map->mapw[mlx->map->mp] - 1;
			mlx->map->disv = cos(degtorad(mlx->map->ra)) * (mlx->map->rx - mlx->map->px) - sin(degtorad(mlx->map->ra)) * (mlx->map->ry - mlx->map->py);
			mlx->map->dof = 15;
		}
		else
		{
			mlx->map->rx += mlx->map->xo;
			mlx->map->ry += mlx->map->yo;
			mlx->map->dof += 1;
		}
	}
}

void	ft_hor_line(t_data *mlx)
{
	mlx->map->dof = 0;
	mlx->map->dish = 1000000000;
	mlx->map->tan = 1.0 / mlx->map->tan;
	if (sin(degtorad(mlx->map->ra)) > 0.001)
	{
		mlx->map->ry = (((int)mlx->map->py >> 6) << 6) -0.001;
		mlx->map->rx = (mlx->map->py - mlx->map->ry) * mlx->map->tan + mlx->map->px;
		mlx->map->yo = -64;
		mlx->map->xo = -mlx->map->yo * mlx->map->tan;
	}
	else if (sin(degtorad(mlx->map->ra)) < -0.001)
	{
		mlx->map->ry = (((int)mlx->map->py >> 6) << 6) + 64;
		mlx->map->rx = (mlx->map->py - mlx->map->ry) * mlx->map->tan + mlx->map->px;
		mlx->map->yo = 64;
		mlx->map->xo = -mlx->map->yo * mlx->map->tan;
	}
	else
	{
		mlx->map->rx = mlx->map->px;
		mlx->map->ry = mlx->map->py;
		mlx->map->dof = 15;
	}
	while (mlx->map->dof < 15)
	{
		mlx->map->mx = (int)(mlx->map->rx) >> 6;
		mlx->map->my = (int)(mlx->map->ry) >> 6;
		mlx->map->mp = mlx->map->my * mlx->map->mapx + mlx->map->mx;
		if (mlx->map->mp > 0 && mlx->map->mp < mlx->map->mapx * mlx->map->mapy && mlx->map->mapw[mlx->map->mp] > 0)
		{
			mlx->map->hmt = mlx->map->mapw[mlx->map->mp] - 1;
			mlx->map->dish = cos(degtorad(mlx->map->ra)) * (mlx->map->rx - mlx->map->px) - sin(degtorad(mlx->map->ra)) * (mlx->map->ry - mlx->map->py);
			mlx->map->dof = 15;
		}
		else
		{
			mlx->map->rx += mlx->map->xo;
			mlx->map->ry += mlx->map->yo;
			mlx->map->dof += 1;
		}
	}
}

void	ft_raycast(t_data *mlx)
{
	mlx->map->r = 8;
	mlx->map->ra = ft_fixang(mlx->map->pa + 30);
	mlx->map->r = 0;
	while (mlx->map->r < 120)
	{
		mlx->map->vmt = 0;
		mlx->map->hmt = 0;
		mlx->map->mv = 0;
		mlx->map->mh = 0;
		ft_vert_line(mlx);
		mlx->map->vx = mlx->map->rx;
		mlx->map->vy = mlx->map->ry;
		ft_hor_line(mlx);
		mlx->map->color = 0x008000;
		mlx->map->shade = 1;
		if (mlx->map->disv <= mlx->map->dish)
		{
			mlx->map->hmt = mlx->map->vmt;
			mlx->map->shade = 0.5;
			mlx->map->rx = mlx->map->vx;
			mlx->map->ry = mlx->map->vy;
			mlx->map->dish = mlx->map->disv;
			mlx->map->color  = 0xFF0000;
		}
		mlx->map->ca = ft_fixang(mlx->map->pa - mlx->map->ra);
		mlx->map->dish = mlx->map->dish * cos(degtorad(mlx->map->ca));
		mlx->map->lineh = (64 * 470) / mlx->map->dish;
		mlx->map->ty_step = 32.0 / (float)mlx->map->lineh;
		mlx->map->ty_off = 0;
		if (mlx->map->lineh > 470)
		{
			mlx->map->ty_off = (mlx->map->lineh - 470) / 2.0;
			mlx->map->lineh = 470;
		}
		mlx->map->depth[mlx->map->r] = mlx->map->dish;
		mlx->map->lineo = 250 - (mlx->map->lineh >> 1);
		mlx->map->ty = mlx->map->ty_off * mlx->map->ty_step;
		if (mlx->map->shade == 1)
		{
			mlx->map->tx = (int)(mlx->map->rx / 2.0) % 32;
			if (mlx->map->ra > 180)
				mlx->map->tx = 31 - mlx->map->tx;
		}
		else
		{
			mlx->map->tx = (int)(mlx->map->ry / 2.0) % 32;
			if (mlx->map->ra > 90 && mlx->map->ra < 270)
				mlx->map->tx = 31 - mlx->map->tx;
		}
		int y;
		y = 0;
		while (y < mlx->map->lineh)
		{
			int pixel=((int)mlx->map->ty*32+(int)mlx->map->tx)*3+(mlx->map->hmt*32*32*3);
			int red =All_Textures[pixel+0]*mlx->map->shade;
			int green =All_Textures[pixel+1]*mlx->map->shade;
			int blue =All_Textures[pixel+2]*mlx->map->shade;
			int tempx = mlx->map->r * 8;
			mlx->map->color = (red << 16 | green << 8 | blue);
			while (tempx < ((mlx->map->r * 8) + 8))
			{
				my_mlx_pixel_put(mlx, tempx, y + mlx->map->lineo, mlx->map->color);
				tempx++;
			}
			mlx->map->ty += mlx->map->ty_step;
			y++;
		}
		mlx->map->ra = ft_fixang(mlx->map->ra - 0.5);
		mlx->map->r++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

int ft_draw(t_data *mlx)
{
	(void)mlx;
	clear(mlx);
	ft_key_hook(mlx);
	ft_raycast(mlx);
	ft_map_draw(mlx);
	mlx_hook(mlx->win_ptr, 2, (1L << 0), ft_key_d, mlx);
    mlx_hook(mlx->win_ptr, 3, 1L << 1, ft_key_u, mlx);
	return (0);
}

void	ft_create_level(t_data *mlx)
{
	mlx->map->color = 0x00FFFF;
	mlx->map->depth = (int *)malloc(sizeof(float) * 1200);
	ft_map_convert(mlx);
	ft_get_player_pos(mlx);
	mlx->map->pa = 0;
	mlx->map->pdx = cos(degtorad(mlx->map->pa));
	mlx->map->pdy = sin(degtorad(mlx->map->pa));
	printf("player found at x: %d y: %d\n", mlx->map->px, mlx->map->py);
	mlx_loop_hook(mlx->mlx_ptr, ft_draw, mlx);

}