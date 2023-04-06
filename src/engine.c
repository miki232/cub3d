/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:18:20 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/06 17:57:55 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int mawp[]=           //the map array. Edit to change level but keep the outer walls
{
    1,1,1,1,1,2,2,3,
    1,0,0,1,0,0,0,1,
    1,0,0,4,0,2,0,1,
    1,0,0,1,0,0,0,1,
    1,0,0,0,0,2,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

int mapX=8, mapY=8, mapS=64; //map size and scale
int depth[120];

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

float	degtorad(float a)
{
	return (a * M_PI / 180.0);
}

float	ft_fixang(float a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
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
		mlx->map->pa -= 8 * 0.8;
		mlx->map->pa = ft_fixang(mlx->map->pa);
		mlx->map->pdx = cos(degtorad(mlx->map->pa));
		mlx->map->pdy = -sin(degtorad(mlx->map->pa));
	}
	if (key == 125) //giu
	{
		mlx->map->py -= mlx->map->pdy * 7;
		mlx->map->px -= mlx->map->pdx * 7;
	}
	if (key == 126) //su
	{
		mlx->map->py += mlx->map->pdy * 7;
		mlx->map->px += mlx->map->pdx * 7;
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
		if (mlx->map->map[i] >= '1')
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
			y += 10;
		}
		else
			x += 10;
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
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
		mlx->map->dof = 0;
		mlx->map->disv = 1000000;
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
			mlx->map->rx = (((int)mlx->map->px >> 6) << 6) -0.0001;
			mlx->map->ry = (mlx->map->px - mlx->map->rx) * mlx->map->tan + mlx->map->py;
			mlx->map->xo = -64;
			mlx->map->yo = -mlx->map->xo * mlx->map->tan;
		}
		else
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
			if (mlx->map->mp > 0 && mlx->map->mp < mapX * mapY && mawp[mlx->map->mp] > 0)
			{
				mlx->map->vmt = mawp[mlx->map->mp] - 1;
				mlx->map->disv = cos(degtorad(mlx->map->ra)) * (mlx->map->rx - mlx->map->px) - sin(degtorad(mlx->map->ra)) * (mlx->map->ry - mlx->map->py);
				mlx->map->dof = 8;
			}
			else
			{
				mlx->map->rx += mlx->map->xo;
				mlx->map->ry += mlx->map->yo;
				mlx->map->dof += 1;
			}
		}
		mlx->map->vx = mlx->map->rx;
		mlx->map->vy = mlx->map->ry;
		///hor
		mlx->map->dof = 0;
		mlx->map->dish = 1000000;
		mlx->map->tan = 1.0 / mlx->map->tan;
		if (sin(degtorad(mlx->map->ra)) > 0.001)
		{
			mlx->map->ry = (((int)mlx->map->py >> 6) << 6) -0.0001;
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
			mlx->map->dof = 8;
		}
		while (mlx->map->dof < 8)
		{
			mlx->map->mx = (int)(mlx->map->rx) >> 6;
			mlx->map->my = (int)(mlx->map->ry) >> 6;
			mlx->map->mp = mlx->map->my * mapX + mlx->map->mx;
			if (mlx->map->mp > 0 && mlx->map->mp < mapX * mapY && mawp[mlx->map->mp] > 0)
			{
				mlx->map->hmt = mawp[mlx->map->mp] - 1;
				mlx->map->dish = cos(degtorad(mlx->map->ra)) * (mlx->map->rx - mlx->map->px) - sin(degtorad(mlx->map->ra)) * (mlx->map->ry - mlx->map->py);
				mlx->map->dof = 8;
			}
			else
			{
				mlx->map->rx += mlx->map->xo;
				mlx->map->ry += mlx->map->yo;
				mlx->map->dof += 1;
			}
		}
		mlx->map->color = 0x008000;
		mlx->map->shade = 1;
		if (mlx->map->disv < mlx->map->dish)
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
		mlx->map->lineh = (mapS * 322) / mlx->map->dish;
		mlx->map->ty_step = 32.0 / (float)mlx->map->lineh;
		mlx->map->ty_off = 0;
		if (mlx->map->lineh > 322)
		{
			mlx->map->ty_off = (mlx->map->lineh - 322) / 2.0;
			mlx->map->lineh = 322;
		}
		depth[mlx->map->r] = mlx->map->dish;
		mlx->map->lineo = 162 - (mlx->map->lineh >> 1);
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
			int tempx = mlx->map->r * 5;
			while (tempx < ((mlx->map->r * 5) + 5))
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
	clear(mlx);
	ft_map_draw(mlx);
	ft_raycast(mlx);
	mlx_hook(mlx->win_ptr, 2, (1L << 0), ft_key, mlx);
	return (0);
}

int	ft_map_len(t_map *map)
{
	int i;
	int nl;

	nl = 0;
	i = 0;
	while (map->map[i] != '\0')
	{
		if (map->map[i] == '\n')
			nl++;
		i++;
	}
	map->mapy = nl;
	map->mapx = (i - nl) / nl;
	return (i - nl);
}

void	ft_map_convert(t_data *mlx)
{
	int i;
	int m_len;

	i = 0;
	m_len = ft_map_len(mlx->map);
	mlx->map->mapw = (int *)ft_calloc(m_len, sizeof(int));
	while (mlx->map->map[i] != '\0')
	{
		if (mlx->map->map[i] == '\n')
		{
			i++;
			continue;
		}
		mlx->map->mapw[i] = ft_atoi(&mlx->map->map[i]);
		i++;
	}
	i = 0;
	printf("%d\n", m_len);
	printf("%d\n", mlx->map->mapy);
	printf("%d\n", mlx->map->mapx);
	// while (i < m_len)
	// {
	// 	printf("%d", mlx->map->mapw[i]);
	// 	i++;
	// }
}

void	ft_create_level(t_data *mlx)
{
	mlx->map->color = 0x00FFFF;
	ft_map_convert(mlx);
	// ft_Ft(mlx);
	// ft_get_player_pos(mlx);
	// mlx->map->pa = 90;
	// // mlx->map->px = 150;
	// // mlx->map->py = 400;
	// mlx->map->pdx = cos(degtorad(mlx->map->pa));
	// mlx->map->pdy = sin(degtorad(mlx->map->pa));
	// mlx_loop_hook(mlx->mlx_ptr, ft_draw, mlx);

	// ft_square(mlx, 0, 0, 0x00FF0000);
	printf("player found at x: %d y: %d\n", mlx->map->px, mlx->map->py);
	// mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 50, 0);
}