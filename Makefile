# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 16:44:05 by rmamzer           #+#    #+#              #
#    Updated: 2025/06/26 12:24:56 by rmamzer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
#CHECK FLAGS BEFORE SUBMISSION. ALSO FOR FUTURE: -Ofast
C_FLAGS = -Wall -Wextra -Werror -Wunreachable-code -g

MLX42_DIR = ./MLX42
MLX42 = $(MLX42_DIR)/build/libmlx42.a

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a


OBJS_DIR = objs/
SRCS_DIR = srcs/

HEADERS = -I ./include -I $(MLX42_DIR)/include -I $(LIBFT_DIR)
MLX42_LIBS =  $(MLX42) -ldl -lglfw -pthread -lm

SRCS =  main.c check_file.c

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
.SECONDARY: ${OBJS}

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


# Do i need to add headers
$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(C_FLAGS) $(OBJS) $(LIBFT) $(MLX42_LIBS) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(LIBFT)
	rm -rf $(MLX42_DIR)/build

re: fclean all

.PHONY: all re clean fclean


