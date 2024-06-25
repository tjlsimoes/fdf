NAME := fdf

LIBFT := libft/libft.a
MINILIBX := mlx_linux/libmlx.a
PRINTF := printf/libftprintf.a

CC := cc

CFLAGS := -Wall -Wextra -Werror
DEBUG_FLAGS = -g

SRC := main.c
OBJ := $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJ)
	cd mlx_linux && $(MAKE)
	$(CC) $(CFLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

#$(NAME): $(OBJ)
#	cd printf && $(MAKE)
#	cd libft && $(MAKE) clean
#	cd mlx_linux && $(MAKE)
#	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX) -o $(NAME)
## $(CC) $(CFLAGS) $(OBJ) $(PRINTF) $(LIBFT) -o $(NAME)
## $(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	cd mlx_linux && $(MAKE) clean
#	cd printf && $(MAKE) clean
#	cd libft && $(MAKE) clean
	$(RM) $(OBJ)

fclean: clean
	cd mlx_linux && $(MAKE) clean
#	cd printf && $(MAKE) fclean
#	cd libft && $(MAKE) fclean
	$(RM) $(NAME)

# minilibx only has a fclean rule with named 'clean'.

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(OBJ)
	cd mlx_linux && $(MAKE)
	$(CC) $(CFLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

# debug: $(OBJ)
# 	cd printf && $(MAKE)
# 	cd libft && $(MAKE) debug
# 	$(CC) -g $(CFLAGS) $(OBJ) $(MINILIBX) -o $(NAME)
# $(CC) -g $(CFLAGS) $(OBJ) $(PRINTF) $(LIBFT) -o $(NAME)

re: fclean all

.PHONY: all bonus debug bdebug clean fclean re
# https://www.baeldung.com/linux/a-so-extension-files
# https://medium.com/@ayogun/makefile-basics-beginner-intermediate-c92377542c2c