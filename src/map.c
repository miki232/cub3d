/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:14:41 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/10 19:49:19 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	*ft_skip(char *line)
{
	int i;
	int j;
	
	i = 2;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[j] != '\n')
		j++;
	line[j] = '\0';
	return (line + i);
}


void	map_load(t_data *mlx, char *line)
{
	if (line[ft_strlen(line) - 1] == '\n')
		mlx->map->maprow++;
	if ((int)ft_strlen(line) > mlx->map->l_mapex)
		mlx->map->l_mapex = ft_strlen(line);
	mlx->map->tempmap = ft_matrixextend(mlx->map->tempmap, line);
}

int	ft_line(char *line, t_data *mlx)
{
	int i;
	i = 0;
	if (line == NULL)
		return (-1);
	if (line[i] == 'N' && line[i + 1] == 'O')
		mlx->map->no_texture = ft_strdup(ft_skip(line));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		mlx->map->so_texture = ft_strdup(ft_skip(line));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		mlx->map->we_texture = ft_strdup(ft_skip(line));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		mlx->map->ea_texture = ft_strdup(ft_skip(line));
	else if (line[i] == '1' || line[i] == ' ')
		map_load(mlx, line); 
	return (1);
}

void    ft_freeline(char *line)
{
    int i;

    i = -1;
    if (line == NULL)
        return;
    while (line[++i] != '0')
        free(&line[i]);
}

// void	ft_map_draw(t_data *mlx)
// {
// 	int i;
// 	int x;
// 	int y;

// 	i = 0;
// 	x = 0;
// 	y = 0;
// 	while (mlx->map->map[i])
// 	{
// 		if (mlx->map->map[i] >= '1')
// 			ft_square(mlx, x, y, 0x00FF0000);
// 		else if (mlx->map->map[i] == '0')
// 			ft_square(mlx, x, y, 0x00000FF0);
// 		else if (mlx->map->map[i] == 'N')
// 		{
// 			ft_square(mlx, x, y, 0x00000FF0);

// 		}
// 		if (mlx->map->map[i] == '\n')
// 		{
// 			x = 0;
// 			y += 10;
// 		}
// 		else
// 			x += 10;
// 		i++;
// 	}
// 	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
// }

void	ft_map_fill(t_data *mlx)
{
	int i;

	i = 0;
	mlx->map->map = (char **)ft_calloc(mlx->map->maprow + 1, sizeof(char *));
	while (i < mlx->map->maprow)
	{
		mlx->map->map[i] = (char *)ft_calloc(mlx->map->l_mapex, sizeof(char));
		int x = 0;
		while (x < mlx->map->l_mapex - 1)
		{
			mlx->map->map[i][x] = '7';
			x++;
		}
		mlx->map->map[i][x] = '\0';
		x = 0;
		while (mlx->map->tempmap[i][x] != '\n')
		{
			if (mlx->map->tempmap[i][x] != ' ')
				mlx->map->map[i][x] = mlx->map->tempmap[i][x];
			x++;
		}
		i++;
	}
}

// int ft_map_check(t_data *mlx)
// {
// 	int	i;
// 	int	j;
	
// 	j = 0;
// 	i = 0;
// 	while (mlx->map->tempmap[i] != NULL)
// 	{
// 		j = 0;
// 		while (mlx->map->tempmap[i][j] == ' ')
// 		{
// 			/* code */
// 		}
		
// 	}
	
// }

void	ft_map_parser(t_data *mlx, char *file)
{
	char	*line;
	int		ret;
	int		fd;
	
	ret = 0;
	line = NULL;
	fd = open(file, O_RDONLY);
	if (line == NULL)
		ret = 1;
	while (ret == 1)
	{
		line = get_next_line(fd);
		ret = ft_line(line, mlx);
		free(line);
	}
	
    //ft_freeline(line);
	// printf("%s\n", map->no_texture);
	// printf("%s\n", map->so_texture);
	// printf("%s\n", map->we_texture);
	// printf("%s\n", map->ea_texture);
	// ft_map_check(mlx);
	ft_map_fill(mlx);
	ret = 0;
	while (mlx->map->tempmap[ret] != NULL)
	{
		printf("%s", mlx->map->tempmap[ret]);
		ret++;
	}
	printf("\n");
	ret = 0;
	while (mlx->map->map[ret] != NULL)
	{
		printf("%s\n", mlx->map->map[ret]);
		ret++;
	}
	printf("\nl_mapex = %d row = %d\n", mlx->map->l_mapex, mlx->map->maprow);
	close(fd);
}