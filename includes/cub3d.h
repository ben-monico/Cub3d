/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/24 00:31:43 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <mlx.h>
# include <allocs.h>
# include <str.h>
# include <stdio.h>
# include <unistd.h>
# include <parse.h>
# include <img.h>
# include <math.h>

# include <img.h>
# include <math.h>


# if MACKEYMAP == 1
#  define KEY_ESC	53
#  define KEY_W		13
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define LEFT 		123
#  define RIGHT 	124
#  define ARROW_LEFT 	65361
#  define ARROW_RIGHT	65363
# else
#  define KEY_ESC		65307
#  define KEY_W			119
#  define KEY_A 		97
#  define KEY_S 		115
#  define KEY_D 		100
#  define ARROW_UP 		65362
#  define ARROW_DOWN 	65364
#  define ARROW_LEFT 	65361
#  define ARROW_RIGHT	65363
#  endif

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17
# define screenW				1000
# define screenH				1000
# define SIZE_X					64
# define SIZE_Y					64
# define COLOR_TRANSPARENT 		0xd411aa

typedef struct s_cub	t_cub;
typedef struct s_line	t_line;
typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_dist	t_dist;
typedef struct s_img	t_img;


struct		s_img
{
	void	**img;
	int		colors[2];
};

struct s_line
{
	int	floorPoint;
	int	ceilingPoint;
	int	x;
};

struct s_dist
{
	double  rayDirX;
    double  rayDirY;
	double  sideDistX;
    double  sideDistY;
    double  deltaDistX;
    double  deltaDistY;
    int stepX;
    int stepY;
    int mapX;
    int mapY;
	int	wallSide;
};

struct	s_map
{
	char	**mtx;
	int		player_x;
	int		player_y;
	char	p_orientation;
	int		num_player;
	int		*f_c;
	int		*c_c;
};

struct		s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	fovX;
	double	fovY;
};

struct s_cub
{
    void		*mlx;
	void		*win;
    int			**map_mtx;
	t_map		map;
	t_img		img;
	t_player	player;
};


t_cub	*new_cube(void);
// Mlx Utils
void	load_img(t_cub *data, char **path);
void	create_cube(t_cub *cub);
int		press_key(int key, t_cub *cub);

// Raycastin Utils
void    raycasting(t_cub *cub);
void	init_raycast_vars(t_cub *cub);

// Read File and Create Map
int		read_file(t_cub *cube, char *file_name, int ac);
void	read_map(t_cub *cube);
void	check_map_elements(t_cub *cub);

// Clean and Exit Program
void	exit_free(t_cub *data, int status, char *str);
int		close_window(t_cub *vars);

// Parsing Resources
int		get_map(char **file, t_cub *cube);

// Moving
void w_press(t_cub *cub);
void a_press(t_cub *cub);
void s_press(t_cub *cub);
void d_press(t_cub *cub);
void a_left_press(t_cub *cub);
void a_right_press(t_cub *cub);


#endif