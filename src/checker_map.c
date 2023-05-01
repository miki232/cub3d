/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:46:46 by mtoia             #+#    #+#             */
/*   Updated: 2023/04/13 10:46:46 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../include/cub.h"

bool	is_valid_position(int rows, int cols, int x, int y)
{
	return (x >= 0 && x < rows && y >= 0 && y < cols);
}

int	is_zero_enclosed_by_one(char **matrix, int rows, int cols)
{
	int	dx[]= {-1, -1, -1, 0, 0, 1, 1, 1};
	int	dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	bool	visited[rows][cols];
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			visited[i][j] = false;
			j++;
		}
		i++;
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (matrix[i][j] == '0' && !visited[i][j])
			{
				bool is_enclosed = true;
				visited[i][j] = true;
				int queue_x[rows * cols];
				int queue_y[rows * cols];
				int front = 0, rear = 0;
				queue_x[rear] = i;
				queue_y[rear] = j;
				rear++;

				while (front != rear) {
					int x = queue_x[front];
					int y = queue_y[front];
					front++;

					for (int k = 0; k < 8; k++) {
						int nx = x + dx[k];
						int ny = y + dy[k];

						if (is_valid_position(rows, cols, nx, ny) && matrix[nx][ny] == '0' && !visited[nx][ny])
						{
							visited[nx][ny] = true;
							queue_x[rear] = nx;
							queue_y[rear] = ny;
							rear++;
						}
						else if (!is_valid_position(rows, cols, nx, ny) || matrix[nx][ny] == '7')
						{
							is_enclosed = false;
						}
					}
				}
				if (is_enclosed)
				{
					continue;
				} else
				{
					return (0);
				}
			}
		}
	}
	return (1);
}

int validate_map(char **matrix, int rows, int cols)
{
    int player_position_found = 0;
    char valid_chars[] = "7 01NSEW";

    // Verifica che la mappa sia circondata da muri (1)
    for (int i = 0; i < rows; i++) {
        if (matrix[i][0] != '1' || matrix[i][cols - 1] != '1') {
            return 0;
        }
    }
    for (int j = 0; j < cols; j++) {
        if (matrix[0][j] != '1' || matrix[rows - 1][j] != '1') {
            return 0;
        }
    }

    // Controlla se i caratteri sono validi e se c'è una posizione del giocatore
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char current_char = matrix[i][j];
            bool is_valid_char = false;

            for (int k = 0; valid_chars[k] != '\0'; k++) {
                if (current_char == valid_chars[k]) {
                    is_valid_char = true;
                    break;
                }
            }

            if (!is_valid_char) {
                return 0;
            }

            if (current_char == 'N' || current_char == 'S' || current_char == 'E' || current_char == 'W') {
                if (player_position_found == 2) {
                    // Troppi giocatori sulla mappa
                    return 2;
                }
                player_position_found ++;
            }
        }
    }

    if (!player_position_found) {
        // Nessuna posizione del giocatore trovata
        return 0;
    }

    // Verifica se gli zeri sono racchiusi da "1"
    if (is_zero_enclosed_by_one(matrix, rows, cols) == 0) {
        return 0;
    }

    return 1;
}

void	ft_check_map(t_data *mlx)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (mlx->map->map[i] != NULL)
	{
		j = 0;
		while (mlx->map->map[i][j] != '\0')
		{
			if (mlx->map->map[i][j] == '0')
			{
				if (mlx->map->map[i - 1][j] == ' ' || mlx->map->map[i + 1][j] == ' ' || mlx->map->map[i][j - 1] == ' ' || mlx->map->map[i][j + 1] == ' ' || mlx->map->map[i][j + 1] == '\0')
					ft_error("Error\nMap is not closed");
			}
			j++;
		}
		i++;
	}
	
}