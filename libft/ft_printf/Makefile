NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

CC = cc

SRCS = ft_printf.c ft_utilities.c

OBJS = $(SRCS:.c=.o)
.SECONDARY: ${OBJS}

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
