# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 16:40:12 by mtoia             #+#    #+#              #
#    Updated: 2023/03/20 17:24:32 by mtoia            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

C_LGRN = \033[92m
C_LMGN = \033[95m
C_END = \033[0m

SRC = src/main.c src/map.c

MLX = mlx/libmlx.a

CC = gcc -g

FLAGS = -Werror -Wextra -Wall -g

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./mlx
	@make -C ./libft
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L libft -lft -lm $(MLX) -framework OpenGL -framework AppKit
	@echo "$(C_LGRN)➜ [$(NAME)] Program has been compiled successfully !$(C_END)"

%.o: %.c
	@${CC} ${FLAGS} -c $< -o $@

clean:
	@make -C ./libft fclean
	@make -C ./mlx clean
	@rm -f $(OBJ)
	@echo "$(C_LMGN)➜ [$(NAME)] Objects have been cleaned successfully !$(C_END)"

fclean:
	@make -C ./mlx clean
	@make -C ./libft fclean
	@rm -f $(NAME) $(OBJ)
	@echo "$(C_LMGN)➜ [$(NAME)] Objects has been deleted successfully !$(C_END)"

re: fclean $(NAME)

run: all

.PHONY: all clean fclean re run