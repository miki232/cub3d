/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:39:17 by mtoia             #+#    #+#             */
/*   Updated: 2023/03/27 17:15:06 by mtoia            ###   ########.fr       */
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

int	ft_key(int key, t_data *mlx)
{
	if (key == 124)
	{
		
        mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, mlx->map->player_x, mlx->map->player_y);
		printf("%d  %d\n", mlx->map->player_x, mlx->map->player_y);
		mlx->map->player_x += 10;
	}
	
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	mlx;

	mlx.map = (t_map *)calloc(1, sizeof(t_map));
	if (argc != 2)
	{
		printf("Error\n");
		return (0);
	}
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	ft_map_parser(&mlx, argv[1]);
	ft_create_level(&mlx);
	// ft_free(&map);
	mlx.img = mlx_new_image(mlx.mlx_ptr, 10, 10);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	ft_square(&mlx, 0xFFFF00);
	printf("player found at x: %d y: %d\n", mlx.map->player_x, mlx.map->player_y);
	mlx_hook(mlx.win_ptr, 2, 0, ft_key, &mlx);
	mlx_loop(&mlx.mlx_ptr);
}