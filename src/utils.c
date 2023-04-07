/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:21:59 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/07 14:47:24 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void    ft_square(t_data *mlx, int x, int y, int colo)
{
    int tempx;
    int tempy;

    tempx = x;
    tempy = y;
    while (tempy < (y + 10))
    {
        tempx = x;
        while (tempx < (x + 10))
        {
            my_mlx_pixel_put(mlx, tempx, tempy, colo);
            tempx++;
        }
        tempy++;
    }
}

//for line drawing, only for dev purposes
void drawline(int x0, int y0, int x1, int y1, t_data *mlx)
{
//   if (x1 > HEIGHT || y1 > WIDTH || x0 > HEIGHT || y0 > WIDTH)
//     return ;
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 
  for (;;){  /* loop */
    my_mlx_pixel_put(mlx, x0, y0, 0xFFFFFF);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}
//ang to de-void
float   dist(float ax, float ay, float bx, float by, float ang) 
{
    (void)ang;
    return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}

void    ft_player(t_data *mlx, int x, int y, int colo)
{
    int tempx;
    int tempy;

    tempx = x;
    tempy = y;
    while (tempy < (y + 20))
    {
        tempx = x;
        while (tempx < (x + 20))
        {
            my_mlx_pixel_put(mlx, tempx, tempy, colo);
            tempx++;
        }
        tempy++;
    }
}

float	ft_fixang(float a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

float	degtorad(float a)
{
	return (a * M_PI / 180.0);
}