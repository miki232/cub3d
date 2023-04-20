/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:39:17 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/17 14:49:08 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_free(t_data *mlx)
{
	free(mlx->map->no_texture);
	mlx->map->no_texture = NULL;
	free(mlx->map->so_texture);
	mlx->map->so_texture = NULL;
	free(mlx->map->we_texture);
	mlx->map->we_texture = NULL;
	free(mlx->map->ea_texture);
	mlx->map->ea_texture = NULL;
	ft_matrixfree(mlx->map->map);
	ft_matrixfree(mlx->map->tempmap);
	

	mlx->map->map = NULL;
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	mlx;

	(void)argv;
	mlx.map = (t_map *)calloc(1, sizeof(t_map));
	mlx.key = (t_key *)calloc(1, sizeof(t_key));
	if (argc != 2)
	{
		printf("Error\n");
		return (0);
	}
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH + 1, HEIGHT + 1, "CUB3D");
	mlx.img = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, \
			&mlx.line_length, &mlx.endian);
	mlx.map->ra_step = 0.5;
	ft_map_parser(&mlx, argv[1]);
	ft_create_level(&mlx);
	// ft_free(&map);
	mlx_loop(mlx.mlx_ptr);
}
