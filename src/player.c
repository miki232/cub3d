/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:58:18 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/13 11:58:24 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_get_player_pos(t_data *mlx)
{
	int	i;
	int	x;
	int	k;
	int	y;

	i = -1;
	x = 0;
	y = 0;
	while (mlx->map->map[++i] != NULL)
	{
		k = -1;
		while (mlx->map->map[i][++k] != '\0')
		{
			if (mlx->map->map[i][k] == '7' || mlx->map->map[i][k] == '1' ||
					mlx->map->map[i][k] == '0')
				x += 64;
			if (mlx->map->map[i][k] == 'N')
			{
				mlx->map->px = x + 32;
				mlx->map->py = y + 32;
			}
		}
		x = 0;
		y += 64;
	}
}
