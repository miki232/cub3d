/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:00:03 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/13 12:05:35 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_map_conv_helpr(t_data *mlx, int m_len)
{
	mlx->map->mapx = mlx->map->l_mapex;
	mlx->map->mapy = mlx->map->maprow;
	mlx->map->mapw = (int *)ft_calloc(m_len, sizeof(int));
}

void	ft_map_convert(t_data *mlx)
{
	int	i;
	int	j;
	int	k;
	int	m_len;

	i = 0;
	j = 0;
	k = 0;
	m_len = mlx->map->l_mapex * mlx->map->maprow;
	ft_map_conv_helpr(mlx, m_len);
	while (mlx->map->map[i] != NULL)
	{
		k = 0;
		while (mlx->map->map[i][k] != '\0')
		{
			if (mlx->map->map[i][k] == 'N')
				mlx->map->mapw[j] = 0;
			else
				mlx->map->mapw[j] = mlx->map->map[i][k] - 48;
			j++;
			k++;
		}
		i++;
	}
	printf("mapx: %d, mapy: %d m_len : %d\n", mlx->map->mapx, mlx->map->mapy, m_len); ///debug
	i = 0;
	while (i < m_len)
	{
		if (i % mlx->map->mapx == 0)
			printf("  %d \n", i);
		printf("%d", mlx->map->mapw[i]);
		i++;
	}
	printf("  %d \n", i);
	///end debug
}
