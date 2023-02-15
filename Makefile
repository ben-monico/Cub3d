SRC =	$(SRC_DIR)/main.c	\
		$(SRC_DIR)/resources.c


OBJ 	= $(substr $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

SRC_DIR = srcs

OBJ_DIR = objs

NAME 	= cub3d

CFLAGS 	= -Wall -Wextra -Werror -g -I$(INC) -fsanitize=address

MLXFLAG = -lXext -lX11 -lm -lz

RM		= rm -rf

INC		= includes/

CC 		= gcc


all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux $(MLXFLAG) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I/usr/local/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 