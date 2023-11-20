/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:14:41 by mtoia             #+#    #+#             */
/*   Updated: 2023/05/01 15:59:58 by mtoia            ###   ########.fr       */
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

void update_probabilities(char *line, t_data *m) {
    int in_number = 0;

    for (int i = 0; i < (int)ft_strlen(line); i++) {
        char c = line[i];
        if (c == ' ') {
            m->map->num_spots++;
            in_number = 0;
        } else {
            if (!in_number) {
                m->map->num_numbers++;
                in_number = 1;
            }
        }
    }
}

double calculate_probabilities(t_data *m) {
    double prob_spaces = (double) m->map->num_spots / (double) m->map->num_numbers;
    double prob_numbers = 1 - prob_spaces;

    return prob_numbers > prob_spaces ? prob_numbers : prob_spaces;
}

char *ft_rl_space(t_data *mlx, int k)
{
	int i = 0;
	int j = 0;
	char *temp;
	
	temp = (char *)calloc(ft_strlen(mlx->map->tempmap[k]), sizeof(char));
	while (mlx->map->tempmap[k][i] != '\0')
	{
		if (mlx->map->tempmap[k][i] != ' ' && mlx->map->tempmap[k][i] != '\n')
		{
			temp[j] = mlx->map->tempmap[k][i];
			j++;
		}
		if (mlx->map->tempmap[k][i] == ' ' && mlx->map->tempmap[k][i + 1] == ' ')
		{
			temp[j] = '7';
			j++;
			i++;
		}
		i++;
	}
	temp[j + 1]	= '\0';
	return (temp);
}

void	map_load(t_data *mlx, char *line)
{
	if (line[ft_strlen(line) - 1] == '\n')
		mlx->map->maprow++;
	if ((int)(ft_strlen(line) - 1) > mlx->map->l_mapex)
		mlx->map->l_mapex = (ft_strlen(line) - 1);
	mlx->map->tempmap = ft_matrixextend(mlx->map->tempmap, line);
	update_probabilities(line, mlx);
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
	else if ((line[i] == '1' || line[i] == ' '))
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

void	ft_map_draw(t_data *mlx)
{
	int i;
	int x;
	int	k;
	int y;

	i = 0;
	x = 0;
	y = 0;
	k = 0;
	while (mlx->map->map[i])
	{
		k = 0;
		while (mlx->map->map[i][k] != '\0')
		{
			if (mlx->map->map[i][k] >= '1')
				ft_square(mlx, x, y, 0x808080);
			else if (mlx->map->map[i][k] == '0')
				ft_square(mlx, x, y, 0xFFFAAF);
			else if (mlx->map->map[i][k] == 'N')
				ft_square(mlx, x, y, 0x00000FF0);
			x += 5;
			k++;
		}
		x = 0;
		y += 5;
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img->img, 0, 0);
}

void	ft_map_fill(t_data *mlx)
{
	int i;

	i = 0;
	// printf("NUMBERS: %f\n", calculate_probabilities(mlx));
	if (calculate_probabilities(mlx) > 1)
	{
		mlx->map->map = (char **)ft_calloc(mlx->map->maprow + 1, sizeof(char *));
		while (i < mlx->map->maprow)
		{
			mlx->map->map[i] = (char *)ft_calloc(mlx->map->l_mapex, sizeof(char));
			int x = 0;
			while (x < mlx->map->l_mapex)
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
	else
	{
		i = 0;
		mlx->map->l_mapex = 0;
		while (i < mlx->map->maprow)
		{
			mlx->map->map = ft_matrixextend(mlx->map->map, ft_rl_space(mlx, i));
			update_probabilities(mlx->map->map[i], mlx);
			if ((int)ft_strlen(mlx->map->map[i]) > mlx->map->l_mapex)
				mlx->map->l_mapex = ft_strlen(mlx->map->map[i]);
			// printf("%s\n", mlx->map->map[i]);
			i++;
		}
		if (!validate_map(mlx->map->map, mlx->map->maprow, mlx->map->l_mapex))
			ft_error("MAP ERROR\n");
	}
}	


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
	
	ft_map_fill(mlx);
	///debug line
	ret = 0;
	// printf("TEMPMAP\n");
	ft_check_map(mlx);
	
	// printf("\n\n");
	ret = 0;
	if (is_zero_enclosed_by_one(mlx->map->map, mlx->map->maprow, mlx->map->l_mapex))
		printf("OK\n");
	else
		ft_error("MAP ERROR\n");
	// printf("\nl_mapex = %d row = %d\n", mlx->map->l_mapex, mlx->map->maprow);
	close(fd);
}