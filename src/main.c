/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:39:17 by mtoia             #+#    #+#             */
/*   Updated: 2023/05/01 17:14:53 by mtoia            ###   ########.fr       */
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
	mlx.img = (t_image *)calloc(1, sizeof(t_image));
	mlx.imgmlt = (t_image *)calloc(1, sizeof(t_image));
	mlx.multi = (t_multi *)calloc(1, sizeof(t_multi));
	mlx.multi->key = (t_key *)calloc(1, sizeof(t_key));
	if (argc != 2)
	{
		printf("Error\n");
		return (0);
	}
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH*2, HEIGHT, "CUB3D");
	mlx.img->img = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
	mlx.img->addr = mlx_get_data_addr(mlx.img->img, &mlx.img->bits_per_pixel, \
			&mlx.img->line_length, &mlx.img->endian);
			//multiplayer mlx
	mlx.imgmlt->img = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
	mlx.imgmlt->addr = mlx_get_data_addr(mlx.imgmlt->img, &mlx.imgmlt->bits_per_pixel, \
			&mlx.imgmlt->line_length, &mlx.imgmlt->endian);
	mlx.map->ra_step = 0.5;
	ft_map_parser(&mlx, argv[1]);
	ft_create_level(&mlx);
	// ft_free(&map);
	mlx_loop(mlx.mlx_ptr);
}
