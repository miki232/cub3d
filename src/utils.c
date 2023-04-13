/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:21:59 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/13 13:59:22 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_square(t_data *mlx, int x, int y, int colo)
{
	int	tempx;
	int	tempy;

	tempx = x;
	tempy = y;
	while (tempy < (y + 5))
	{
		tempx = x;
		while (tempx < (x + 5))
		{
			my_mlx_pixel_put(mlx, tempx, tempy, colo);
			tempx++;
		}
		tempy++;
	}
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
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

void	ft_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}