/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:18:20 by mtoia             #+#    #+#             */
/*   Updated: 2023/03/31 13:56:25 by mtoia            ###   ########.fr       */
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
			y++;
		}
		else if (mlx->map->map[i] == ' ' || mlx->map->map[i] == '1')
		{
			x++;
		}
		if (mlx->map->map[i] == 'N')
		{
			mlx->map->player_x = x;
			mlx->map->player_y = y;
		}
		i++;
	}
	
}

void	verline(t_data *mlx, int x, int y1, int y2, int color)
{
	while (y1 <= y2)
	{
		my_mlx_pixel_put(mlx, x, y1, color);
		y1++;
	}
	// mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	clear(t_data *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->addr =	mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}

// int ft_key(int key, t_data *mlx)
// {
// 	(void)mlx;
// 	printf("key = %d\n", key);
// 	return (0);
// }

// int cast(t_data *mlx)
// {
// 	double dirX = -1, dirY = 0; //initial direction vector
// 	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
// 	clock_t startTick = clock();
// 	double frameTime;
// 	double time = 0; //time of current frame
// 	double oldTime = 0; //time of previous frame
// 	for (int x = 0; x < WIDTH; x++)
// 		{
// 			calculate ray position and direction
// 			double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
// 			double rayDirX = dirX + planeX * cameraX;
// 			double rayDirY = dirY + planeY * cameraX;
// 			which box of the map we're in
// 			int mapX = (int)(mlx->map->player_x);
// 			int mapY = (int)(mlx->map->player_y);
// 			length of ray from current position to next x or y-side
// 			double sideDistX;
// 			double sideDistY;
// 			length of ray from one x or y-side to next x or y-side
// 			these are derived as:
// 			deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
// 			deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
// 			which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
// 			where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
// 			unlike (dirX, dirY) is not 1, however this does not matter, only the
// 			ratio between deltaDistX and deltaDistY matters, due to the way the DDA
// 			stepping further below works. So the values can be computed as below.
// 			Division through zero is prevented, even though technically that's not
// 			needed in C++ with IEEE 754 floating point values.
// 			double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
// 			double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
// 				double perpWallDist;

// 			what direction to step in x or y-direction (either +1 or -1)
// 			int stepX;
// 			int stepY;

// 			int hit = 0; //was there a wall hit?
// 			int side; //was a NS or a EW wall hit?
// 			calculate step and initial sideDist
// 			if(rayDirX < 0)
// 			{
// 				stepX = -1;
// 				sideDistX = (mlx->map->player_x - mapX) * deltaDistX;
// 			}
// 			else
// 			{
// 				stepX = 1;
// 				sideDistX = (mapX + 1.0 - mlx->map->player_x) * deltaDistX;
// 			}
// 			if(rayDirY < 0)
// 			{
// 				stepY = -1;
// 				sideDistY = (mlx->map->player_y - mapY) * deltaDistY;
// 			}
// 			else
// 			{
// 				stepY = 1;
// 				sideDistY = (mapY + 1.0 - mlx->map->player_y) * deltaDistY;
// 			}
// 			perform DDA
// 			while(hit == 0)
// 			{
// 				jump to next map square, either in x-direction, or in y-direction
// 				if(sideDistX < sideDistY)
// 				{
// 					sideDistX += deltaDistX;
// 					mapX += stepX;
// 					side = 0;
// 				}
// 				else
// 				{
// 					sideDistY += deltaDistY;
// 					mapY += stepY;
// 					side = 1;
// 				}
// 				Check if ray has hit a wall
// 				if(worldMap[mapX][mapY] > 0) hit = 1;
// 			}
// 			// Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
// 			// hit to the camera plane. Euclidean to center camera point would give fisheye effect!
// 			// This can be computed as (mapX - mlx->map->player_x + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
// 			// for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
// 			// because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
// 			// steps, but we subtract deltaDist once because one step more into the wall was taken above.
// 			if(side == 0) perpWallDist = (sideDistX - deltaDistX);
// 			else          perpWallDist = (sideDistY - deltaDistY);

// 			// Calculate height of line to draw on screen
// 			int lineHeight = (int)(HEIGHT / perpWallDist);
// 			// calculate lowest and highest pixel to fill in current stripe
// 			int drawStart = -lineHeight / 2 + HEIGHT / 2;
// 			if(drawStart < 0) drawStart = 0;
// 			int drawEnd = lineHeight / 2 + HEIGHT / 2;
// 			if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
			
// 			verline(mlx, x, drawStart, drawEnd, 0x00FF00);
// 			oldTime = time;
// 			clock_t elapsedTicks = clock() - startTick;
// 			time = (double)elapsedTicks / ((double)CLOCKS_PER_SEC / 1000.0);
// 			frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
// 			printf("%f\n", 1.0 / frameTime); //FPS counter
// 			mlx_hook(mlx->win_ptr, 2, 0, ft_key, mlx);
// 			double oldDirX = dirX;
// 			double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
// 			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
// 			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
// 			double oldPlaneX = planeX;
// 			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
// 			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
			
// 			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
// 			usleep(1000);
// 		}
// 		clear(mlx);
// 		return (0);
// }

int	ft_key(int key, t_data *mlx)
{
	if (key == 124)
	{
		
		double olddirx = mlx->map->dirx;
		mlx->map->dirx = mlx->map->dirx * cos(-mlx->map->rotspeed) - mlx->map->diry * sin(-mlx->map->rotspeed);
		mlx->map->diry = olddirx * sin(-mlx->map->rotspeed) + mlx->map->diry * cos(-mlx->map->rotspeed);
		double oldplanex = mlx->map->planex;
		mlx->map->planex = mlx->map->planex * cos(-mlx->map->rotspeed) - mlx->map->planey * sin(-mlx->map->rotspeed);
		mlx->map->planey = oldplanex * sin(-mlx->map->rotspeed) + mlx->map->planey * cos(-mlx->map->rotspeed);
	}
	if (key == 126)
	{
		if (worldMap[(int)(mlx->map->player_x + mlx->map->dirx * mlx->map->movespeed)][(int)(mlx->map->player_y)] == 0)
			mlx->map->player_x += mlx->map->dirx * mlx->map->movespeed;
		if (worldMap[(int)(mlx->map->player_x)][(int)(mlx->map->player_y + mlx->map->diry * mlx->map->movespeed)] == 0)
			mlx->map->player_y += mlx->map->diry * mlx->map->movespeed;
	}
	return (0);
}


int cast(t_data *mlx)
{
	int x;

	x = 0;
	while (x < WIDTH)
	{
		mlx->map->camerax = 2 * x / (double)WIDTH - 1;
		mlx->map->raydirx = mlx->map->dirx + mlx->map->planex * mlx->map->camerax;
		mlx->map->raydiry = mlx->map->diry + mlx->map->planey * mlx->map->camerax;
		mlx->map->mapx = (int)(mlx->map->player_x);
		mlx->map->mapy = (int)(mlx->map->player_y);
		if (mlx->map->raydirx == 0)
			mlx->map->deltadistx = 1e30;
		else
			mlx->map->deltadistx = fabs(1 / mlx->map->raydirx);
		if (mlx->map->raydiry == 0)
			mlx->map->deltadisty = 1e30;
		else
			mlx->map->deltadisty = fabs(1 / mlx->map->raydiry);
		//calculate step and initial sideDist
		mlx->map->hit = 0;
		if (mlx->map->raydirx < 0)
		{
			mlx->map->stepx = -1;
			mlx->map->sidedistx = (mlx->map->player_x - mlx->map->mapx) * mlx->map->deltadistx;
		}
		else
		{
			mlx->map->stepx = 1;
			mlx->map->sidedistx = (mlx->map->mapx + 1.0 - mlx->map->player_x) * mlx->map->deltadistx;
		}
		if (mlx->map->raydiry < 0)
		{
			mlx->map->stepy = -1;
			mlx->map->sidedisty = (mlx->map->player_y - mlx->map->mapy) * mlx->map->deltadisty;
		}
		else
		{
			mlx->map->stepy = 1;
			mlx->map->sidedisty = (mlx->map->mapy + 1.0 - mlx->map->player_y) * mlx->map->deltadisty;
		}
		//perform DDA
		while (mlx->map->hit == 0)
		{
			if (mlx->map->sidedistx < mlx->map->sidedisty)
			{
				mlx->map->sidedistx += mlx->map->deltadistx;
				mlx->map->mapx += mlx->map->stepx;
				mlx->map->side = 0;
			}
			else
			{
				mlx->map->sidedisty += mlx->map->deltadisty;
				mlx->map->mapy += mlx->map->stepy;
				mlx->map->side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mlx->map->mapx][mlx->map->mapy] > 0)
				mlx->map->hit = 1;
		}
		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (mlx->map->side == 0)
			mlx->map->perpwalldist = (mlx->map->sidedistx - mlx->map->deltadistx);
		else
			mlx->map->perpwalldist = (mlx->map->sidedisty - mlx->map->deltadisty);
		//Calculate height of line to draw on screen
		mlx->map->lineheight = (int)(HEIGHT / mlx->map->perpwalldist);
		//calculate lowest and highest pixel to fill in current stripe
		mlx->map->drawstart = -mlx->map->lineheight / 2 + HEIGHT / 2;
		if (mlx->map->drawstart < 0)
			mlx->map->drawstart = 0;
		mlx->map->drawend = mlx->map->lineheight / 2 + HEIGHT / 2;
		if (mlx->map->drawend >= HEIGHT)
			mlx->map->drawend = HEIGHT - 1;
		verline(mlx, x, mlx->map->drawstart, mlx->map->drawend, 0x00FF00);
		mlx->map->oldtime = mlx->map->time;
		mlx->map->elapsedTicks = clock() - mlx->map->start;
		mlx->map->time = (double)mlx->map->elapsedTicks / ((double)CLOCKS_PER_SEC / 1000000.0);
		mlx->map->frametime = (mlx->map->time - mlx->map->oldtime) / 10000.0;
		mlx->map->movespeed = mlx->map->frametime * 5.0;
		mlx->map->rotspeed = mlx->map->frametime * 3.0; //the constant value is in radians
		//printf("FPS: %f\n", 1.0 / mlx->map->frametime);
		mlx_hook(mlx->win_ptr, 2, 0, ft_key, mlx);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
		x++;
	}
	clear(mlx);
	return (0);
}

void	ft_create_level(t_data *mlx)
{
	// ft_get_player_pos(mlx);
	mlx->map->player_x = 22;
	mlx->map->player_y = 12;
	mlx->map->dirx = -1;
	mlx->map->diry = 0;
	mlx->map->planex = 0;
	mlx->map->planey = 0.66;
	mlx->map->time = 0;
	mlx->map->oldtime = 0;
	mlx->map->frametime = 0;
	mlx->map->hit = 0;
	mlx->map->start = clock();
	mlx_loop_hook(mlx->mlx_ptr, cast, mlx);
}






	// ft_square(mlx, 0xFFFF00);