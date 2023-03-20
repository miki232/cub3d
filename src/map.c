/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:14:41 by mtoia             #+#    #+#             */
/*   Updated: 2023/03/20 17:38:11 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	map_parser(t_data *mlx, char *file)
{
	char	*line;
	int		fd;
	(void)mlx;

	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)) > 0)
	{
		printf("%s", line);
		free(line);
	}
	printf("\n");
	close(fd);
}