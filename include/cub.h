/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:36:30 by mtoia             #+#    #+#             */
/*   Updated: 2023/05/01 17:22:58 by mtoia            ###   ########.fr       */
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
#include <sys/types.h>
#include <unistd.h>

# define HEIGHT 560
# define WIDTH 840
# define PI 3.1415926535
# define P2 PI / 2
# define P3 3*PI / 2
# define DR 0.0174533
# define DOOR 4


typedef struct s_data t_data;
typedef struct s_image t_image;
typedef struct s_key t_key;

typedef struct s_spritess
{
	float dist;
	float dx;
	float dy;
    int type; //static, key, enemy
    int state; //on off
    int map; //texture to show
	float rx;
	float ry;
    float x,y,z; //position
	t_image	*texture;
}		t_spritess;

typedef struct s_textures {
	t_image	*ea;
	t_image	*no;
	t_image	*so;
	t_image	*we;
	t_image	*door[10];
}	t_textures;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_image;


typedef struct	s_multi
{
	int	sprit_num;
	float		px; //player x
	float		py; //player y
	float	pdx; //delta x
	float	pdy; //delta y
	float	pa;	//player angle
	int		r;
	int		on;//enable sprite projectile
	int		mapx;
	int		mapy;
	int		maps;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		side;
	int		vmt;
	int		hmt;
	int		mv;
	int		mh;
	int		color;
	int		temps;
	int		lineh;
	int		*depth;
	float	vx;
	float	vy;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	disv;
	float	dish;
	float	hx;
	float	hy;
	float 	dist;
	float	lineo;
	float	tan;
	float	shade;
	float	ca;
	float 	ty_step;
	float 	ty_off;
	float 	ty;
	float 	tx;
	t_key	*key;
}			t_multi;

typedef struct	s_map
{
	char	**map;
	char	**tempmap;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	float		px; //player x
	float		py; //player y
	float	pdx; //delta x
	float	pdy; //delta y
	float	pa;	//player angle
	float	ra_step;
	int		*mapw;
	int		maprow;
	int		l_mapex;
	int		num_spots;
	int		num_numbers;
	int		mapx;
	int		mapy;
	int		maps;
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		side;
	int		vmt;
	int		hmt;
	int		mv;
	int		mh;
	int		color;
	int		temps;
	int		lineh;
	int		*depth;
	float	vx;
	float	vy;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	disv;
	float	dish;
	float	hx;
	float	hy;
	float 	dist;
	float	lineo;
	float	tan;
	float	shade;
	float	ca;
	float 	ty_step;
	float 	ty_off;
	float 	ty;
	float 	tx;
	t_textures	*textures;
}			t_map;

typedef struct s_key
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		key;
}		t_key;

typedef struct	s_data
{
    void	*mlx_ptr;
	void	*win_ptr;
	t_spritess *sp;
	t_image	*img;
	t_image	*imgmlt;
	t_key	*key;
	t_map	*map;
	t_multi	*multi;

}				t_data;

typedef enum e_keys_map
{
	KB_PAGE_UP = 116,
	KB_PAGE_DOWN = 121,
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	ESC = 53,
	PLUS = 69,
	MINUS = 78,
	RIGHT = 123,
	LEFT = 124,
	UP = 125,
	DOWN = 126,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}	t_keys_map;


/// mlx draw
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void	clear(t_data *mlx);
void	verline(t_data *mlx, int x, int y1, int y2, int color);
void drawline(int x0, int y0, int x1, int y1, t_data *mlx);
unsigned int	get_pixel(t_image *img, int x, int y);
/// map parser
void	ft_map_parser(t_data *mlx, char *file);
void	ft_map_convert(t_data *mlx);
int	ft_map_len(t_map *map);
void	ft_map_draw(t_data *mlx);
int is_zero_enclosed_by_one(char **matrix, int rows, int cols);
void    shoot(t_data *mlx);
/// engine & creation
void	ft_create_level(t_data *mlx);
int	ft_key(int key, t_data *mlx);
void    ft_key_hook(t_data *mlx);
void    movesprite(t_data *mlx, float ex, float ey, float speed);
//utils
void    ft_square(t_data *mlx,int x, int y, int colo);
void    ft_player(t_data *mlx, int x, int y, int colo);
void	verline(t_data *mlx, int x, int y1, int y2, int color);
float	dist(float ax, float ay, float bx, float by);
float	ft_fixang(float a);
float	degtorad(float a);
void	ft_free(t_data *map);
void	ft_get_player_pos(t_data *mlx);
void	ft_error(char *str);
void	ft_check_map(t_data *mlx);
int validate_map(char **matrix, int rows, int cols);
void    drawSprite(t_data *mlx, float px, float py, float pa, int *depth, int m, t_image *data);
void	ft_multy_raycast(t_data *mlx);
//key handler
int	ft_key_u(int key, t_data *mlx);
int	ft_key_d(int key, t_data *mlx);
float distance(float ax, float ay, float bx, float by);

#endif