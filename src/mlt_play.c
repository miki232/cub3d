/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlt_play.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:24:41 by mtoia             #+#    #+#             */
/*   Updated: 2023/05/01 16:02:33 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_vert_line2(t_data *mlx)
{
	mlx->multi->dof = 0;
	mlx->multi->disv = 1000000;
	mlx->multi->tan = tan(degtorad(mlx->multi->ra));
	if (cos(degtorad(mlx->multi->ra)) > 0.001)
	{
		mlx->multi->rx = (((int)mlx->multi->px >> 6) << 6) + 64;
		mlx->multi->ry = (mlx->multi->px - mlx->multi->rx) * mlx->multi->tan + mlx->multi->py;
		mlx->multi->xo = 64;
		mlx->multi->yo = -mlx->multi->xo * mlx->multi->tan;
	}
	else if (cos(degtorad(mlx->multi->ra)) < -0.001)
	{
		mlx->multi->rx = (((int)mlx->multi->px >> 6) << 6) -0.001;
		mlx->multi->ry = (mlx->multi->px - mlx->multi->rx) * mlx->multi->tan + mlx->multi->py;
		mlx->multi->xo = -64;
		mlx->multi->yo = -mlx->multi->xo * mlx->multi->tan;
	}
	else
	{
		mlx->multi->rx = mlx->multi->px;
		mlx->multi->ry = mlx->multi->py;
		mlx->multi->dof = 15;
	}
	while (mlx->multi->dof < 15)
	{
		mlx->multi->mx = (int)(mlx->multi->rx) >> 6;
		mlx->multi->my = (int)(mlx->multi->ry) >> 6;
		mlx->multi->mp = mlx->multi->my * mlx->multi->mapx + mlx->multi->mx;
		if (mlx->multi->mp > 0 && mlx->multi->mp < mlx->multi->mapx * mlx->multi->mapy && mlx->map->mapw[mlx->multi->mp] > 0)
		{
			// mlx->multi->vmt = mlx->multi->multiw[mlx->multi->mp] - 1;
			if (mlx->map->mapw[mlx->multi->mp] == DOOR)
				mlx->multi->vmt = 4;
			mlx->multi->disv = cos(degtorad(mlx->multi->ra)) * (mlx->multi->rx - mlx->multi->px) - sin(degtorad(mlx->multi->ra)) * (mlx->multi->ry - mlx->multi->py);
			mlx->multi->dof = 15;
		}
		else
		{
			mlx->multi->rx += mlx->multi->xo;
			mlx->multi->ry += mlx->multi->yo;
			mlx->multi->dof += 1;
		}
	}
}

void	ft_hor_line2(t_data *mlx)
{
	mlx->multi->dof = 0;
	mlx->multi->dish = 1000000;
	mlx->multi->tan = 1.0 / mlx->multi->tan;
	if (sin(degtorad(mlx->multi->ra)) > 0.001)
	{
		mlx->multi->ry = (((int)mlx->multi->py >> 6) << 6) -0.001;
		mlx->multi->rx = (mlx->multi->py - mlx->multi->ry) * mlx->multi->tan + mlx->multi->px;
		mlx->multi->yo = -64;
		mlx->multi->xo = -mlx->multi->yo * mlx->multi->tan;
	}
	else if (sin(degtorad(mlx->multi->ra)) < -0.001)
	{
		mlx->multi->ry = (((int)mlx->multi->py >> 6) << 6) + 64;
		mlx->multi->rx = (mlx->multi->py - mlx->multi->ry) * mlx->multi->tan + mlx->multi->px;
		mlx->multi->yo = 64;
		mlx->multi->xo = -mlx->multi->yo * mlx->multi->tan;
	}
	else
	{
		mlx->multi->rx = mlx->multi->px;
		mlx->multi->ry = mlx->multi->py;
		mlx->multi->dof = 15;
	}
	while (mlx->multi->dof < 15)
	{
		mlx->multi->mx = (int)(mlx->multi->rx) >> 6;
		mlx->multi->my = (int)(mlx->multi->ry) >> 6;
		mlx->multi->mp = mlx->multi->my * mlx->multi->mapx + mlx->multi->mx;
		if (mlx->multi->mp > 0 && mlx->multi->mp < mlx->multi->mapx * mlx->multi->mapy && mlx->map->mapw[mlx->multi->mp] > 0)
		{
			// mlx->multi->hmt = mlx->multi->multiw[mlx->multi->mp] - 1;
			if (mlx->map->mapw[mlx->multi->mp] == DOOR)
				mlx->multi->vmt = 4;
			mlx->multi->dish = cos(degtorad(mlx->multi->ra)) * (mlx->multi->rx - mlx->multi->px) - sin(degtorad(mlx->multi->ra)) * (mlx->multi->ry - mlx->multi->py);
			mlx->multi->dof = 15;
		}
		else
		{
			mlx->multi->rx += mlx->multi->xo;
			mlx->multi->ry += mlx->multi->yo;
			mlx->multi->dof += 1;
		}
	}
}

void	ft_multy_raycast(t_data *mlx)
{
	mlx->multi->ra = ft_fixang(mlx->multi->pa + 30);
	mlx->multi->r = 0;
	while (mlx->multi->r < WIDTH)
	{
		mlx->multi->vmt = 0;
		mlx->multi->hmt = 0;
		mlx->multi->mv = 0;
		mlx->multi->mh = 0;
		ft_vert_line2(mlx);
		mlx->multi->vx = mlx->multi->rx;
		mlx->multi->vy = mlx->multi->ry;
		ft_hor_line2(mlx);
		// mlx->multi->color = 0x008000;
		mlx->multi->shade = 1;
		if (mlx->multi->disv < mlx->multi->dish)
		{
			// mlx->multi->hmt = mlx->multi->vmt;
			mlx->multi->shade = 0.5;
			mlx->multi->rx = mlx->multi->vx;
			mlx->multi->ry = mlx->multi->vy;
			mlx->multi->dish = mlx->multi->disv;
			// mlx->multi->color  = 0xFF0000;
		}
		mlx->multi->ca = ft_fixang(mlx->multi->pa - mlx->multi->ra);
		mlx->multi->dish = mlx->multi->dish * cos(degtorad(mlx->multi->ca));
		mlx->multi->lineh = (64 * HEIGHT) / mlx->multi->dish;
		mlx->multi->ty_step = 32.0 / (float)mlx->multi->lineh;
		mlx->multi->ty_off = 0;
		if (mlx->multi->lineh > HEIGHT)
		{
			mlx->multi->ty_off = (mlx->multi->lineh - HEIGHT) / 2.0;
			mlx->multi->lineh = HEIGHT;
		}
		mlx->multi->depth[mlx->multi->r] = mlx->multi->dish;
		mlx->multi->lineo = (HEIGHT / 2) - (mlx->multi->lineh >> 1);
		mlx->multi->ty = mlx->multi->ty_off * mlx->multi->ty_step;
		if (mlx->multi->shade == 1)
		{
			mlx->multi->hmt = 0; //Nord
			mlx->multi->tx = (int)(mlx->multi->rx / 2.0) % 32;
			if (mlx->multi->ra > 180)
			{
				mlx->multi->hmt = 1; //SUd
				mlx->multi->tx = 31 - mlx->multi->tx;
			}
		}
		else
		{
			// printf("SUCA\n");
			mlx->multi->tx = (int)(mlx->multi->ry / 2.0) % 32;
			mlx->multi->hmt = 3; //Est
			if (mlx->multi->ra > 90 && mlx->multi->ra < 270)
			{
				mlx->multi->hmt = 2; //Ouest
				mlx->multi->tx = 31 - mlx->multi->tx;
			}
		}
		if (mlx->multi->vmt > mlx->multi->hmt)
			mlx->multi->hmt = 3;
		int y;
		y = 0;
		while (y < mlx->multi->lineh)
		{
			int tempx = mlx->multi->r * 1;
			while (tempx < ((mlx->multi->r * 1) + 1))
			{ 
				if (mlx->multi->hmt == 0)
					my_mlx_pixel_put(mlx->imgmlt, tempx, y + mlx->multi->lineo, get_pixel(mlx->map->textures->no, mlx->multi->tx, mlx->multi->ty));
				else if (mlx->multi->hmt == 3)
					my_mlx_pixel_put(mlx->imgmlt, tempx, y + mlx->multi->lineo, get_pixel(mlx->map->textures->ea, mlx->multi->tx, mlx->multi->ty));
				else if (mlx->multi->hmt == 1)
					my_mlx_pixel_put(mlx->imgmlt, tempx, y + mlx->multi->lineo, get_pixel(mlx->map->textures->so, mlx->multi->tx, mlx->multi->ty));
				else if (mlx->multi->hmt == 2)
					my_mlx_pixel_put(mlx->imgmlt, tempx, y + mlx->multi->lineo, get_pixel(mlx->map->textures->we, mlx->multi->tx, mlx->multi->ty));
				// my_mlx_pixel_put(mlx, tempx, y + mlx->multi->lineo, mlx->multi->color);
				tempx++;
			}
			mlx->multi->ty += mlx->multi->ty_step;
			y++;
		}
		mlx->multi->ra = ft_fixang(mlx->multi->ra - 0.071);
		mlx->multi->r++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->imgmlt->img, 840, 0);
}