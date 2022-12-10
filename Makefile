# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2022/01/14 12:09:38 by tgriffit          #+#    #+#             #
#   Updated: 2022/12/02 16:28:55 by tgriffit         ###   ########lyon.fr   #
#																			 #
# ************************************************************************** #

NAME = cub3D

FLAGS = -Wall -Wextra -Werror
#FLAGS += -fsanitize=address -g3
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
MLXLIB = -L ./minilibx_macos
DIR_SRCS = ./
DIR_SRCS_PARSING = ./parsing/
DIR_SRCS_CONTROLS = ./controls/
DIR_SRCS_PAINTER = ./painter/
DIR_SRCS_UTILS = ./mlx_utils/
DIR_SRCS_BONUS = ./bonus/
DIR_OBJS = .objs

SRCS = $(DIR_SRCS_UTILS)cub3d_utils.c \
		$(DIR_SRCS_UTILS)sound_no_op.c \
		$(DIR_SRCS_UTILS)quit_cub3d.c \
		./get_next_line/get_next_line_bonus.c \
		main.c \
		$(DIR_SRCS_PARSING)map_header.c \
		$(DIR_SRCS_PARSING)map_parsing.c \
		$(DIR_SRCS_PARSING)map_convert.c \
		$(DIR_SRCS_PARSING)map_enclosed.c \
		$(DIR_SRCS_PARSING)colors_header.c \
		$(DIR_SRCS_CONTROLS)keys.c \
		$(DIR_SRCS_CONTROLS)keys_execute.c \
		$(DIR_SRCS_CONTROLS)hooks.c \
		$(DIR_SRCS_PAINTER)image.c \
		$(DIR_SRCS_PAINTER)stripe.c \
		$(DIR_SRCS_PAINTER)dda.c \
		$(DIR_SRCS_PAINTER)render.c \
		$(DIR_SRCS_PAINTER)painter.c \
		$(DIR_SRCS_PAINTER)sprite.c \
		$(DIR_SRCS_PAINTER)sprite_sort.c \
		$(DIR_SRCS_PAINTER)lifebar.c \
		$(DIR_SRCS_PAINTER)gameover.c \
		$(DIR_SRCS_PAINTER)painter_line.c \
		$(DIR_SRCS_BONUS)minimap_bonus.c \
		$(DIR_SRCS_BONUS)minimap_icons_bonus.c \
        $(DIR_SRCS_BONUS)compass_bonus.c

SRCS_BONUS = $(DIR_SRCS_BONUS)sound_bonus.c \
			 $(DIR_SRCS_BONUS)doors_bonus.c


OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: libftmake mlxmake $(NAME)

$(NAME): $(OBJS)
	@gcc  $(OBJS) $(FLAGS) $(MLXFLAGS) $(MLXLIB) -L libft -lft -o $(NAME)
	@echo "CUB3D: \033[1;32m[READY TO USE]\033[0m\nUsage: ./cub3d <maps/mapname.cub>."
	@echo "Put your maps' textures into the \"textures\" folder."
	@echo "\033[1;34mMOVE with WASD. Turn the camera with LEFT and RIGHT arrows, \
or with LEFT CLICK."
	@echo "Take DAMAGES by pressing [P].\033[0m \nEnjoy!"

%.o : %.c cub3d.h Makefile
	@gcc $(FLAGS) -c $< -o $@

#### LIBFT ####
libftmake:
	@make -C libft
	@echo Libft "\033[1;32mcompiled\033[0m"

libftclean:
	@make fclean -C ./libft/
	@echo Libft cleaned.
##############

mlxmake:
	@make -C minilibx_macos
	@cp minilibx_macos/libmlx.a .
	@echo "Minilibx \033[1;32mcompiled\033[0m"

mlxclean:
	@make -C minilibx_macos clean
	@rm libmlx.a
	@echo Minilibx cleaned.

bonus: libftmake mlxmake $(OBJS) $(OBJS_BONUS)
	@gcc $(OBJS)  $(OBJS_BONUS) $(FLAGS) $(MLXFLAGS) $(MLXLIB) -L libft -lft -o $(NAME)
	@echo "CUB3D is ready to use! Usage: ./cub3D <mapname.cub>\nEnjoy!"

clean:
	rm $(OBJS)

fclean: libftclean clean mlxclean

re: fclean all

.PHONY: all clean fclean re libftmake libftclean mlxmake bonus
#.SILENT:
