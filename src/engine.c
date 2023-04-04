/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:18:20 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/04 17:46:15 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int map[]=           //the map array. Edit to change level but keep the outer walls
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,
};

int mapX=8, mapY=8, mapS=64; //map size and scale 

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
			y+= 64;
		}
		else if (mlx->map->map[i] == ' ' || mlx->map->map[i] == '1' || mlx->map->map[i] == '0')
		{
			x+= 64;
		}
		if (mlx->map->map[i] == 'N')
		{
			mlx->map->px = x + 32;
			mlx->map->py = y + 32;
		}
		i++;
	}
	printf("px = %d\n", mlx->map->px);
	printf("py = %d\n", mlx->map->py);
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
		mlx->map->py -= mlx->map->pdy;
		mlx->map->px -= mlx->map->pdx;
	}
	if (key == 126) //su
	{
		mlx->map->py += mlx->map->pdy;
		mlx->map->px += mlx->map->pdx;
	}
	return (0);
}

void	ft_map_draw(t_data *mlx)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
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
			y += 64;
		}
		else
			x += 64;
		i++;
	}
	drawline(mlx->map->px, mlx->map->py, mlx->map->px + mlx->map->pdx * 5, mlx->map->py + mlx->map->pdy * 5, mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

void drawVerticalWall(int r, int lineOff, int lineH, int color, t_data *mlx)
{
    my_mlx_pixel_put(mlx, r*8+530, lineOff, color); // draw top of wall
    for (int i = 1; i <= lineH; i++) {
         my_mlx_pixel_put(mlx, r*8+530, lineOff+i, color); // draw wall segment
    }
}

void	ft_raycast(t_data *mlx)
{
	float	atan;
	mlx->map->ra = mlx->map->pa - DR * 30;
	if (mlx->map->ra < 0)
		mlx->map->ra += 2 * PI;
	if (mlx->map->ra > 2 * PI)
		mlx->map->ra -= 2 * PI;
	mlx->map->r = 0;
	while (mlx->map->r < 60)
	{
		////// Horizontal RAYCASTING
		mlx->map->dof = 0;
		mlx->map->dish = 1000000;
		mlx->map->hx = mlx->map->px;
		mlx->map->hy = mlx->map->py;
		atan = -1 / tan(mlx->map->ra);
		if (mlx->map->ra > PI)
		{
			mlx->map->ry = (((int)mlx->map->py >> 6) << 6) - 0.0001;
			mlx->map->rx = (mlx->map->py - mlx->map->ry) * atan + mlx->map->px;
			mlx->map->yo = -64;
			mlx->map->xo = -mlx->map->yo * atan;
		}
		if (mlx->map->ra < PI)
		{
			mlx->map->ry = (((int)mlx->map->py >> 6) << 6) + 64;
			mlx->map->rx = (mlx->map->py - mlx->map->ry) * atan + mlx->map->px;
			mlx->map->yo = 64;
			mlx->map->xo = -mlx->map->yo * atan;
		}
		if (mlx->map->ra == 0 || mlx->map->ra == PI)
		{
			mlx->map->rx = mlx->map->px;
			mlx->map->ry = mlx->map->py;
			mlx->map->dof = 8;
		}
		while (mlx->map->dof < 8)
		{
			mlx->map->mx = (int)(mlx->map->rx) >> 6;
			mlx->map->my = (int)(mlx->map->ry) >> 6;
			mlx->map->mp = mlx->map->my * mapX + mlx->map->mx;
			if (mlx->map->mp > 0 && mlx->map->mp < mapX * mapY && map[mlx->map->mp] == 1)
			{
				mlx->map->hx = mlx->map->rx;
				mlx->map->hy = mlx->map->ry;
				mlx->map->dish = dist(mlx->map->px, mlx->map->py, mlx->map->hx, mlx->map->hy, mlx->map->ra);
				mlx->map->dof = 8;
			}
			else
			{
				mlx->map->rx += mlx->map->xo;
				mlx->map->ry += mlx->map->yo;
				mlx->map->dof += 1;
			}
		}
		////// Vertical RAYCASTING
		mlx->map->disv = 1000000;
		mlx->map->vx = mlx->map->px;
		mlx->map->vy = mlx->map->py;
		mlx->map->dof = 0;
		float ntan;
		ntan = -tan(mlx->map->ra);
		if (mlx->map->ra > P2 && mlx->map->ra < P3)
		{
			mlx->map->rx = (((int)mlx->map->px >> 6) << 6) - 0.0001;
			mlx->map->ry = (mlx->map->px - mlx->map->rx) * ntan + mlx->map->py;
			mlx->map->xo = -64;
			mlx->map->yo = -mlx->map->xo * ntan;
		}
		if (mlx->map->ra < P2 || mlx->map->ra > P3)
		{
			mlx->map->rx = (((int)mlx->map->px >> 6) << 6) + 64;
			mlx->map->ry = (mlx->map->px - mlx->map->rx) * ntan + mlx->map->py;
			mlx->map->xo = 64;
			mlx->map->yo = -mlx->map->xo * ntan;
		}
		if (mlx->map->ra == 0 || mlx->map->ra == PI)
		{
			mlx->map->rx = mlx->map->px;
			mlx->map->ry = mlx->map->py;
			mlx->map->dof = 8;
		}
		while (mlx->map->dof < 8)
		{
			mlx->map->mx = (int)(mlx->map->rx) >> 6;
			mlx->map->my = (int)(mlx->map->ry) >> 6;
			mlx->map->mp = mlx->map->my * mapX + mlx->map->mx;
			if (mlx->map->mp > 0 && mlx->map->mp < mapX * mapY && map[mlx->map->mp] == 1)
				mlx->map->dof = 8;
			else
			{
				mlx->map->vx = mlx->map->rx;
				mlx->map->vy = mlx->map->ry;
				mlx->map->disv = dist(mlx->map->px, mlx->map->py, mlx->map->vx, mlx->map->vy, mlx->map->ra);
				mlx->map->rx += mlx->map->xo;
				mlx->map->ry += mlx->map->yo;
				mlx->map->dof += 1;
			}
		}
		if (mlx->map->disv < mlx->map->dish)
		{
			mlx->map->rx = mlx->map->vx;
			mlx->map->ry = mlx->map->vy;
			mlx->map->dist = mlx->map->disv;
		}
		if (mlx->map->dish < mlx->map->disv)
		{
			mlx->map->rx = mlx->map->hx;
			mlx->map->ry = mlx->map->hy;
			mlx->map->dist = mlx->map->dish;
		}
		mlx->map->ra+= DR;
		if (mlx->map->ra < 0)
			mlx->map->ra += 2 * PI;
		if (mlx->map->ra > 2 * PI)
			mlx->map->ra -= 2 * PI;
		drawline(mlx->map->px, mlx->map->py, mlx->map->rx, mlx->map->ry, mlx);
		///Draw 3D
		mlx->map->lineh = (mapS*320) / mlx->map->dist;
		if (mlx->map->lineh > 320)
			mlx->map->lineh = 320;
		mlx->map->lineo = 160 - mlx->map->lineh / 2;
		drawVerticalWall(mlx->map->r, mlx->map->lineo, mlx->map->lineh, 0xFF0000, mlx);
		mlx->map->r++;
		
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

int ft_draw(t_data *mlx)
{
	clear(mlx);
	ft_map_draw(mlx);
	ft_raycast(mlx);
	mlx_hook(mlx->win_ptr, 2, (1L << 0), ft_key, mlx);
	return (0);
}

void	ft_create_level(t_data *mlx)
{
	ft_get_player_pos(mlx);
	mlx->map->pdx = cos(mlx->map->pa) * 5;
	mlx->map->pdy = sin(mlx->map->pa) * 5;
	mlx_loop_hook(mlx->mlx_ptr, ft_draw, mlx);

	// ft_square(mlx, 0, 0, 0x00FF0000);
	printf("player found at x: %d y: %d\n", mlx->map->px, mlx->map->py);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}