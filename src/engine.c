/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:18:20 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/20 19:53:15 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
# include "../src/All_Textures.ppm"
# include "Untitled.ppm"

unsigned int	get_pixel(t_data *img, int x, int y)
{
	char	*dest;

	if (x <= 0 || x >= 64 || y <= 0 || y >= 64)
		return (1);
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dest);
}

void	ft_vert_line(t_data *mlx)
{
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
			// mlx->map->vmt = mlx->map->mapw[mlx->map->mp] - 1;
			if (mlx->map->mapw[mlx->map->mp] == DOOR)
				mlx->map->vmt = 4;
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
	mlx->map->dish = 1000000;
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
			// mlx->map->hmt = mlx->map->mapw[mlx->map->mp] - 1;
			if (mlx->map->mapw[mlx->map->mp] == DOOR)
				mlx->map->vmt = 4;
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
	mlx->map->ra = ft_fixang(mlx->map->pa + 30);
	mlx->map->r = 0;
	while (mlx->map->r < 800)
	{
		mlx->map->vmt = 0;
		mlx->map->hmt = 0;
		mlx->map->mv = 0;
		mlx->map->mh = 0;
		ft_vert_line(mlx);
		mlx->map->vx = mlx->map->rx;
		mlx->map->vy = mlx->map->ry;
		ft_hor_line(mlx);
		// mlx->map->color = 0x008000;
		mlx->map->shade = 1;
		if (mlx->map->disv < mlx->map->dish)
		{
			// mlx->map->hmt = mlx->map->vmt;
			mlx->map->shade = 0.5;
			mlx->map->rx = mlx->map->vx;
			mlx->map->ry = mlx->map->vy;
			mlx->map->dish = mlx->map->disv;
			// mlx->map->color  = 0xFF0000;
		}
		mlx->map->ca = ft_fixang(mlx->map->pa - mlx->map->ra);
		mlx->map->dish = mlx->map->dish * cos(degtorad(mlx->map->ca));
		mlx->map->lineh = (64 * 500) / mlx->map->dish;
		mlx->map->ty_step = 32.0 / (float)mlx->map->lineh;
		mlx->map->ty_off = 0;
		if (mlx->map->lineh > 500)
		{
			mlx->map->ty_off = (mlx->map->lineh - 500) / 2.0;
			mlx->map->lineh = 500;
		}
		mlx->map->depth[mlx->map->r] = mlx->map->dish;
		mlx->map->lineo = 250 - (mlx->map->lineh >> 1);
		mlx->map->ty = mlx->map->ty_off * mlx->map->ty_step;
		if (mlx->map->shade == 1)
		{
			mlx->map->hmt = 0; //Nord
			mlx->map->tx = (int)(mlx->map->rx / 2.0) % 32;
			if (mlx->map->ra > 180)
			{
				mlx->map->hmt = 1; //SUd
				mlx->map->tx = 31 - mlx->map->tx;
			}
		}
		else
		{
			// printf("SUCA\n");
			mlx->map->tx = (int)(mlx->map->ry / 2.0) % 32;
			mlx->map->hmt = 3; //Est
			if (mlx->map->ra > 90 && mlx->map->ra < 270)
			{
				mlx->map->hmt = 2; //Ouest
				mlx->map->tx = 31 - mlx->map->tx;
			}
		}
		if (mlx->map->vmt > mlx->map->hmt)
			mlx->map->hmt = 3;
		int y;
		y = 0;
		while (y < mlx->map->lineh)
		{
			int pixel=((int)mlx->map->ty*32+(int)mlx->map->tx)*3+(mlx->map->hmt*32*32*3);
			int red = d_b[pixel+0]*mlx->map->shade;
			int green = d_b[pixel+1]*mlx->map->shade;
			int blue = d_b[pixel+2]*mlx->map->shade;
			int tempx = mlx->map->r * 1;
			mlx->map->color = (red << 16 | green << 8 | blue);
			while (tempx < ((mlx->map->r * 1) + 1))
			{
				if (mlx->map->hmt == 0)
					my_mlx_pixel_put(mlx, tempx, y + mlx->map->lineo, get_pixel(mlx->map->textures->no, mlx->map->tx, mlx->map->ty));
				else if (mlx->map->hmt == 3)
					my_mlx_pixel_put(mlx, tempx, y + mlx->map->lineo, get_pixel(mlx->map->textures->ea, mlx->map->tx, mlx->map->ty));
				else if (mlx->map->hmt == 1)
					my_mlx_pixel_put(mlx, tempx, y + mlx->map->lineo, get_pixel(mlx->map->textures->so, mlx->map->tx, mlx->map->ty));
				else if (mlx->map->hmt == 2)
					my_mlx_pixel_put(mlx, tempx, y + mlx->map->lineo, get_pixel(mlx->map->textures->we, mlx->map->tx, mlx->map->ty));
				// my_mlx_pixel_put(mlx, tempx, y + mlx->map->lineo, mlx->map->color);
				tempx++;
			}
			mlx->map->ty += mlx->map->ty_step;
			y++;
		}
		mlx->map->ra = ft_fixang(mlx->map->ra - 0.080);
		mlx->map->r++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

int ft_draw(t_data *mlx)
{
	(void)mlx;
	clear(mlx);
	ft_raycast(mlx);
	ft_key_hook(mlx);
	ft_map_draw(mlx);
	mlx_hook(mlx->win_ptr, 2, (1L << 0), ft_key_d, mlx);
    mlx_hook(mlx->win_ptr, 3, 1L << 1, ft_key_u, mlx);
	return (0);
}

static t_data *load(t_data *mlx, char *s)
{
	t_data	*data;
	int		a;
	int		b;

	data = malloc(sizeof(t_data));
	a = 64;
	b = 64;
	data->img = mlx_png_file_to_image(mlx->mlx_ptr, s, &a, &b);
	if (data->img == NULL)
	{
		free(data);
		return (NULL);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (data);
	
}

void	ft_create_level(t_data *mlx)
{
	mlx->map->textures = malloc(sizeof(t_textures));
	mlx->map->textures->ea = load(mlx, "src/wall_ea.png");
	mlx->map->textures->no = load(mlx, "src/wall_no.png");
	mlx->map->textures->so = load(mlx, "src/wall_so.png");
	mlx->map->textures->we = load(mlx, "src/wall_we.png");
	mlx->map->color = 0x00FFFF;
	mlx->map->depth = (int *)malloc(sizeof(float) * 1200);
	ft_map_convert(mlx);
	ft_get_player_pos(mlx);
	mlx->map->pa = 90;
	mlx->map->pdx = cos(degtorad(mlx->map->pa));
	mlx->map->pdy = -sin(degtorad(mlx->map->pa));
	printf("player found at x: %f y: %f\n", mlx->map->px, mlx->map->py);
	mlx_loop_hook(mlx->mlx_ptr, ft_draw, mlx);

}