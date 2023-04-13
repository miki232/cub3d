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

void	ft_map_convert(t_data *mlx)
{
	int i;
	int j;
    int k;
	int m_len;

	i = 0;
	j = 0;
    k = 0;
	m_len = mlx->map->l_mapex * mlx->map->maprow;
    mlx->map->mapx = mlx->map->l_mapex;
    mlx->map->mapy = mlx->map->maprow;
	mlx->map->mapw = (int *)ft_calloc(m_len, sizeof(int));
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
	printf("mapx: %d, mapy: %d m_len : %d\n", mlx->map->mapx, mlx->map->mapy, m_len);
	i = 0;
	while (i < m_len)
	{
		if (i % mlx->map->mapx == 0)
			printf("  %d \n", i);
		printf("%d", mlx->map->mapw[i]);
		i++;
	}
	printf("  %d \n", i);
	
}

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