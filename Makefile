# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 16:44:05 by rmamzer           #+#    #+#              #
#    Updated: 2025/07/08 14:50:21 by rmamzer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

BONUS_NAME = so_long.bonus

CC = cc

C_FLAGS = -Wall -Wextra -Werror

MLX42_DIR = ./MLX42
MLX42 = $(MLX42_DIR)/build/libmlx42.a

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a


OBJS_DIR = objs/
SRCS_DIR = srcs/

BONUS_OBJS_DIR = bonus_objs/
BONUS_SRCS_DIR = bncs/

HEADERS = -I ./include -I $(MLX42_DIR)/include -I $(LIBFT_DIR)

MLX42_LIBS =  $(MLX42) -ldl -lglfw -pthread -lm

SRCS =  main.c check_map.c check_map2.c exit_functions.c get_visuals.c\
		move_functions.c render_visuals.c

BONUS_SRCS = main_bonus.c check_map_bonus.c check_map2_bonus.c \
			exit_functions_bonus.c get_visuals_bonus.c \
			move_functions_bonus.c render_visuals_bonus.c

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
.SECONDARY: ${OBJS}

BONUS_OBJS = $(addprefix $(BONUS_OBJS_DIR), $(BONUS_SRCS:.c=.o))
.SECONDARY: ${BONUS_OBJS}


all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)


$(MLX42_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git $@;

$(MLX42): $(MLX42_DIR)
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build
	@make -C $(MLX42_DIR)/build -j4

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@ $(HEADERS)

$(BONUS_OBJS_DIR)%.o: $(BONUS_SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(C_FLAGS) $(OBJS) $(LIBFT) $(MLX42_LIBS) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(BONUS_OBJS_DIR)
	rm -f .bonus
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) $(LIBFT)
	rm -rf $(MLX42_DIR)/build

re: fclean all

bonus: .bonus

.bonus: $(BONUS_OBJS) $(LIBFT) $(MLX42)
	$(CC) $(C_FLAGS) $(BONUS_OBJS) $(LIBFT) $(MLX42_LIBS) -o $(BONUS_NAME)
	@touch .bonus

.PHONY: all re clean fclean bonus


