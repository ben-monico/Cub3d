SRCS		=	$(SRCS_DIR)/main.c 						\
				$(SRCS_DIR)/gnl/get_next_line.c 		\
				$(SRCS_DIR)/gnl/get_next_line_utils.c	\
				$(SRCS_DIR)/str/str.c					\
				$(SRCS_DIR)/str/utils1.c				\
				$(SRCS_DIR)/str/utils2.c				\
				$(SRCS_DIR)/allocs/allocs.c				

SRCS_DIR	=	srcs

OBJS		=	$(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

OBJS_DIR	=	objs

MLX			=	mlx_linux/libmlx_Linux.a

NAME		=	cub3d

CC			=	cc

INC			=	-Iincludes -I/usr/include -Imlx_linux

CFLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address

RM			=	rm -rf

MLX_FLAGS		= -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

all:		$(NAME)

$(OBJS_DIR)/%.o :	$(SRCS_DIR)/%.c
		mkdir -p $(@D)
		$(CC) $(CFLAGS) $(INC) -O3 -c $< -o $@

$(NAME):	$(PRINTF) $(MLX) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME) $(MLX_FLAGS)

$(MLX):
		make -C mlx_linux

clean:
		$(RM) $(OBJS_DIR)
		make clean -C mlx_linux

fclean:		clean
		$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re