/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:36:30 by mtoia             #+#    #+#             */
/*   Updated: 2023/03/27 17:11:10 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define HEIGHT 480
# define WIDTH 640

typedef struct	s_map
{
	char	*map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		player_x;
	int		player_y;
}			t_map;

typedef struct	s_data
{
    void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	*map;

}				t_data;

/// mlx draw
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/// map parser
void	ft_map_parser(t_data *mlx, char *file);
/// engine & creation
void	ft_create_level(t_data *mlx);

//utils
void    ft_square(t_data *mlx, int colo);

#endif