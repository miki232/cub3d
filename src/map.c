/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:14:41 by mtoia             #+#    #+#             */
/*   Updated: 2023/03/27 16:48:50 by mtoia            ###   ########.fr       */
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
	int i;

	i = 0;
	if (mlx->map->map == NULL)
		mlx->map->map = ft_strdup(line);
	else
		mlx->map->map = ft_strjoin(mlx->map->map, line);
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
	else if (line[i] == '1')
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
    ft_freeline(line);
	// printf("%s\n", map->no_texture);
	// printf("%s\n", map->so_texture);
	// printf("%s\n", map->we_texture);
	// printf("%s\n", map->ea_texture);
	// printf("%s\n", map->map);
	close(fd);
}