/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:00:03 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/10 18:13:59 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// void	ft_map_convert(t_data *mlx)
// {
// 	int i;
// 	int j;
// 	int m_len;
// 	int d_bg;

// 	d_bg = 0;
// 	i = 0;
// 	j = 0;
// 	m_len = ft_map_len(mlx->map);
// 	mlx->map->mapw = (int *)ft_calloc(m_len, sizeof(int));
// 	while (mlx->map->map[i] != '\0')
// 	{
// 		if (mlx->map->map[i] != '\n')
// 		{
// 			if (mlx->map->map[i] == 'N')
// 				mlx->map->mapw[j] = 0;
// 			else
// 				mlx->map->mapw[j] = mlx->map->map[i] - 48;
// 			j++;
// 		}
// 		i++;
// 	}
// 	printf("mapx: %d, mapy: %d m_len : %d\n", mlx->map->mapx, mlx->map->mapy, m_len);
// 	printf("d_bg: %d\n", d_bg);
// 	i = 0;
// 	while (i < m_len)
// 	{
// 		if (i % mlx->map->mapx == 0)
// 			printf("\n");
// 		printf("%d", mlx->map->mapw[i]);
// 		i++;	
// 	}
	
// }

// int	ft_map_len(t_map *map)
// {
// 	int i;
// 	int nl;

// 	nl = 0;
// 	i = 0;
// 	if (map->map == NULL)
// 		return (0);
// 	while (map->map[i] != '\0')
// 	{
// 		if (map->map[i] == '\n')
// 			nl++;
// 		i++;
// 	}
// 	map->mapy = nl;
// 	map->mapx = (i - nl) / nl;
// 	return (i);
// }