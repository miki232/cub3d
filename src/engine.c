/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:18:20 by mtoia             #+#    #+#             */
/*   Updated: 2023/05/01 17:27:26 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
// # include "../src/All_Textures.ppm"
// # include "Untitled.ppm"

unsigned int	get_pixel(t_image *img, int x, int y)
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
		mlx->map->dof = 10;
	}
	while (mlx->map->dof < 10)
	{
		mlx->map->mx = (int)(mlx->map->rx) >> 6;
		mlx->map->my = (int)(mlx->map->ry) >> 6;
		mlx->map->mp = mlx->map->my * mlx->map->mapx + mlx->map->mx;
		if (mlx->map->mp > 0 && mlx->map->mp < mlx->map->mapx * mlx->map->mapy && mlx->map->mapw[mlx->map->mp] > 0)
		{
			mlx->map->disv = cos(degtorad(mlx->map->ra)) * (mlx->map->rx - mlx->map->px) - sin(degtorad(mlx->map->ra)) * (mlx->map->ry - mlx->map->py);
			mlx->map->dof = 10;
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
		mlx->map->dof = 10;
	}
	while (mlx->map->dof < 10)
	{
		mlx->map->mx = (int)(mlx->map->rx) >> 6;
		mlx->map->my = (int)(mlx->map->ry) >> 6;
		mlx->map->mp = mlx->map->my * mlx->map->mapx + mlx->map->mx;
		if (mlx->map->mp > 0 && mlx->map->mp < mlx->map->mapx * mlx->map->mapy && mlx->map->mapw[mlx->map->mp] > 0)
		{
			mlx->map->dish = cos(degtorad(mlx->map->ra)) * (mlx->map->rx - mlx->map->px) - sin(degtorad(mlx->map->ra)) * (mlx->map->ry - mlx->map->py);
			mlx->map->dof = 10;
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
	while (mlx->map->r < WIDTH)
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
			mlx->map->shade = 0.5;
			mlx->map->rx = mlx->map->vx;
			mlx->map->ry = mlx->map->vy;
			mlx->map->dish = mlx->map->disv;
		}
		mlx->map->ca = ft_fixang(mlx->map->pa - mlx->map->ra);
		mlx->map->dish = mlx->map->dish * cos(degtorad(mlx->map->ca));
		mlx->map->lineh = (64 * HEIGHT) / mlx->map->dish;
		mlx->map->ty_step = 32.0 / (float)mlx->map->lineh;
		mlx->map->ty_off = 0;
		if (mlx->map->lineh > HEIGHT)
		{
			mlx->map->ty_off = (mlx->map->lineh - HEIGHT) / 2.0;
			mlx->map->lineh = HEIGHT;
		}
		mlx->map->depth[mlx->map->r] = mlx->map->dish;
		mlx->map->lineo = (HEIGHT / 2) - (mlx->map->lineh >> 1);
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
			int tempx = mlx->map->r * 1;
			while (tempx < ((mlx->map->r * 1) + 1))
			{
				if (mlx->map->hmt == 0)
					my_mlx_pixel_put(mlx->img, tempx, y + mlx->map->lineo, get_pixel(mlx->map->textures->no, mlx->map->tx, mlx->map->ty));
				else if (mlx->map->hmt == 3)
					my_mlx_pixel_put(mlx->img, tempx, y + mlx->map->lineo, get_pixel(mlx->map->textures->ea, mlx->map->tx, mlx->map->ty));
				else if (mlx->map->hmt == 1)
					my_mlx_pixel_put(mlx->img, tempx, y + mlx->map->lineo, get_pixel(mlx->map->textures->so, mlx->map->tx, mlx->map->ty));
				else if (mlx->map->hmt == 2)
					my_mlx_pixel_put(mlx->img, tempx, y + mlx->map->lineo, get_pixel(mlx->map->textures->we, mlx->map->tx, mlx->map->ty));
				tempx++;
			}
			mlx->map->ty += mlx->map->ty_step;
			y++;
		}
		mlx->map->ra = ft_fixang(mlx->map->ra - 0.071);
		mlx->map->r++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img->img, 0, 0);
}

void ft_reset_num_sprite(t_data *mlx)
{
	int i = 0;

	while (i <= mlx->multi->sprit_num)
	{
		if (mlx->sp[i].type == 6)
		{
			// printf("s_num= %d, state= %d\n", i, mlx->sp[i].state);
			// printf("reset sprite num for %d\n", i);
			if (mlx->sp[i].state == 0 && mlx->sp[i+1].state == 0)
				mlx->multi->sprit_num = 2;
			else if (mlx->sp[i].state == 0 && mlx->sp[i+1].state == 1)
			{
				mlx->sp[i].x = mlx->sp[i+1].x;
				mlx->sp[i].y = mlx->sp[i+1].y;
				mlx->sp[i].dx = mlx->sp[i+1].dx;
				mlx->sp[i].dy = mlx->sp[i+1].dy;
				printf("reset sprite num for %d\n", i);
				mlx->sp[i].state = 1;
				mlx->sp[i+1].state = 0;
				mlx->sp[i+1].x = mlx->map->px;
				mlx->sp[i+1].y = mlx->map->py;
				mlx->multi->sprit_num=3;
				break;
			}
			else if (mlx->sp[i].state == 1 && mlx->sp[i+1].state == 0)
			{
				mlx->multi->sprit_num=3;
				break;
			}

			// printf("sprite_num %d\n", mlx->multi->sprit_num);
		}
		i++;
	}
	
}

int ft_draw(t_data *mlx)
{
	// (void)mlx;
	clear(mlx);
	ft_raycast(mlx);
	ft_multy_raycast(mlx);
	ft_key_hook(mlx);
	ft_map_draw(mlx);
	drawSprite(mlx, mlx->multi->px, mlx->multi->py, mlx->multi->pa, mlx->multi->depth, 1, mlx->imgmlt);
	drawSprite(mlx, mlx->map->px, mlx->map->py, mlx->map->pa, mlx->map->depth, 0, mlx->img);
	mlx->sp[0].x=mlx->map->px; mlx->sp[0].y=mlx->map->py;
	mlx->sp[1].x=mlx->multi->px; mlx->sp[1].y=mlx->multi->py;
	ft_reset_num_sprite(mlx);
	return (0);
}

static t_image *load(t_data *mlx, char *s)
{
	t_image	*data;
	int		a;
	int		b;

	data = malloc(sizeof(t_image));
	a = 64;
	b = 64;
	data->img = mlx_xpm_file_to_image(mlx->mlx_ptr, s, &a, &b);
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
	mlx->map->textures->ea = load(mlx, "src/texture/wall_ea.xpm");
	mlx->map->textures->no = load(mlx, "src/texture/wall_no.xpm");
	mlx->map->textures->so = load(mlx, "src/texture/wall_so.xpm");
	mlx->map->textures->we = load(mlx, "src/texture/wall_we.xpm");
	mlx->map->color = 0x00FFFF;
	mlx->map->depth = (int *)malloc(sizeof(float) * 1200);
	mlx->multi->depth = (int *)malloc(sizeof(float) * 1200);
	ft_map_convert(mlx);
	ft_get_player_pos(mlx);
	mlx->map->pa = 90;
	mlx->map->pdx = cos(degtorad(mlx->map->pa));
	mlx->map->pdy = -sin(degtorad(mlx->map->pa));
	mlx->multi->pa = 270;
	mlx->multi->pdx = cos(degtorad(mlx->multi->pa));
	mlx->multi->pdy = -sin(degtorad(mlx->multi->pa));
	mlx->sp = (t_spritess *)calloc(4, sizeof(t_spritess));
	mlx->sp[0].texture = load(mlx, "src/texture/as.xpm");
	mlx->sp[1].texture = load(mlx, "src/texture/as.xpm");
	mlx->sp[2].texture = load(mlx, "src/texture/bullet.xpm");
	mlx->sp[3].texture = load(mlx, "src/texture/bullet.xpm");
	mlx->sp[1].type=3;	mlx->sp[1].state=1;	mlx->sp[1].map=2;	mlx->sp[1].x=mlx->multi->px;  mlx->sp[1].y=mlx->multi->py; 	mlx->sp[1].z=20; //enemy
	mlx->sp[0].type=3; mlx->sp[0].state=1; mlx->sp[0].map=2; mlx->sp[0].x=mlx->map->px; mlx->sp[0].y=mlx->map->py;   mlx->sp[0].z=20; //enemy
	mlx->multi->sprit_num = 2;
	printf("WASD FOR PLAYER 1, ARROWS FOR PLAYER 2\n ------- SPACE FOR FIRE -------\n");
	mlx_hook(mlx->win_ptr, 2, (1L << 0), ft_key_d, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, ft_key_u, mlx);
	mlx_loop_hook(mlx->mlx_ptr, ft_draw, mlx);
	
}