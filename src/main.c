/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:39:17 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/03 18:19:17 by mtoia            ###   ########.fr       */
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
	(void)argv;
	mlx.map = (t_map *)calloc(1, sizeof(t_map));
	if (argc != 2)
	{
		printf("Error\n");
		return (0);
	}
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	mlx.img = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);

	ft_map_parser(&mlx, argv[1]);
	ft_create_level(&mlx);
	// verline(&mlx, 5, 1, 50, 0xFFFFFFF);
	// ft_free(&map);
	
	mlx_loop(mlx.mlx_ptr);
}