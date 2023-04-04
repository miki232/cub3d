/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:36:30 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/04 17:45:21 by mtoia            ###   ########.fr       */
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
# include <time.h>
# include "../mlx/mlx.h"

# define HEIGHT 512
# define WIDTH 1024
# define PI 3.1415926535
# define P2 PI / 2
# define P3 3*PI / 2
# define DR 0.0174533

typedef struct	s_map
{
	char	*map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		px; //player x
	int		py; //player y
	float	pdx; //delta x
	float	pdy; //delta y
	float	pa;	//player angle
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	dish;
	float	hx;
	float	hy;
	float	disv;
	float	vx;
	float	vy;
	float 	dist;
	float	lineh;
	float	lineo;
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
void	clear(t_data *mlx);
void	verline(t_data *mlx, int x, int y1, int y2, int color);
void drawline(int x0, int y0, int x1, int y1, t_data *mlx);

/// map parser
void	ft_map_parser(t_data *mlx, char *file);
/// engine & creation
void	ft_create_level(t_data *mlx);
int	ft_key(int key, t_data *mlx);

//utils
void    ft_square(t_data *mlx,int x, int y, int colo);
void    ft_player(t_data *mlx, int x, int y, int colo);
void	verline(t_data *mlx, int x, int y1, int y2, int color);
float   dist(float ax, float ay, float bx, float by, float ang);

#endif