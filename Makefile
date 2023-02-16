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

NAME		=	cub3d

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address

RM			=	rm -rf

ifeq ($(shell uname), Linux)
MLX			=	mlx_linux/libmlx_Linux.a
MLX_DIR 	= 	mlx_linux
MLX_FLAGS	= 	-Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
INC			=	-I . -Iincludes -I/usr/include -Imlx_linux -O3
else
MLX			=	mlx/libmlx.a
MLX_DIR		= 	mlx
MLX_FLAGS	=	-D MACKEYMAP=1 -Lmlx -lmlx -framework OpenGL -framework AppKit
INC			=	-I . -Iincludes -Imlx
endif

all:		$(NAME)

$(OBJS_DIR)/%.o :	$(SRCS_DIR)/%.c
		mkdir -p $(@D)
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME):	$(PRINTF) $(MLX) $(OBJS)
		$(CC) $(CFLAGS) $(MLX_FLAGS) $(INC) $(OBJS) -o $(NAME) 

$(MLX):
		make -C $(MLX_DIR)

clean:
		$(RM) $(OBJS_DIR)
		make clean -C $(MLX_DIR)

fclean:		clean
		$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re