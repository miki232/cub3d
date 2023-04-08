/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:00:03 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/07 16:07:03 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_map_convert(t_data *mlx)
{
	int i;
	int j;
	int m_len;

	i = 0;
	j = 0;
	m_len = ft_map_len(mlx->map);
	mlx->map->mapw = (int *)ft_calloc(m_len, sizeof(int));
	while (mlx->map->map[i] != '\0')
	{
		if (mlx->map->map[i] != '\n')
		{
			mlx->map->mapw[j] = mlx->map->map[i] - 48;
			if (mlx->map->map[i] == 'N')
				mlx->map->mapw[j] = 0;
			j++;
		}
		i++;
	}
}

int	ft_map_len(t_map *map)
{
	int i;
	int nl;

	nl = 0;
	i = 0;
	if (map->map == NULL)
		return (0);
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