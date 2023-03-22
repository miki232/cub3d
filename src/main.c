/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:39:17 by mtoia             #+#    #+#             */
/*   Updated: 2023/03/22 16:13:08 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_free(t_map *map)
{
	free(map->no_texture);
	map->no_texture = NULL;
	free(map->so_texture);
	map->so_texture = NULL;
	free(map->we_texture);
	map->we_texture = NULL;
	free(map->ea_texture);
	map->ea_texture = NULL;
//	free(map);
}

int	main(int argc, char **argv)
{
	t_data	mlx;
	t_map	map;

	if (argc != 2)
	{
		printf("Error\n");
		return (0);
	}
	map_parser(&map, &mlx, argv[1]);
	ft_free(&map);
	// mlx.mlx_ptr = mlx_init();
	// mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	// mlx_loop(&mlx.mlx_ptr);
}