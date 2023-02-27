/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmonico <benmonico@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/23 19:48:16 by benmonico        ###   ########.fr       */
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

# if MACKEYMAP == 1
#  define KEY_ESC	53
#  define KEY_W		13
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define ARROW_LEFT 	123
#  define ARROW_RIGHT	124
# else
#  define KEY_ESC		65307
#  define KEY_W			119
#  define KEY_A 		97
#  define KEY_S 		115
#  define KEY_D 		100
#  define ARROW_LEFT 	65361
#  define ARROW_RIGHT	65363
#  endif

# define screenW				640
# define screenH				480
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17
# define SIZE_X					64
# define SIZE_Y					64

typedef struct s_cub	t_cub;
typedef struct s_img	t_img;
typedef struct s_line	t_line;
typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_dist	t_dist;

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

struct		s_img
{
	int		**img;
	void	*ptr;
	char	*addr;
	int		colors[2];
	int		bpp;	//when using ARGB this value is always 32
	int		size_line;	//This value represents (your image width) * 4 which I will also explain after
	int		endian;		//This value can be either 0 or 1 and will indicate how the ARGB bytes are organized (from front to back or back to front)
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


t_cub	*new_cub(void);
// Mlx Utils
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	load_img(t_cub *data, char **path);

// Raycastin Utils
void    raycasting(t_cub *cub);

// Read File and Create Map
int		read_file(t_cub *cub, char *file_name);
int		read_map(t_cub *cub);
void	check_map_elements(t_cub *cub);

// Clean Program
void	exit_free(t_cub *data, int status, char *str);

// Parsing Resources
int		get_map(char **file, t_cub *cub);

// Moving
void w_press(t_cub *cub);
void a_press(t_cub *cub);
void s_press(t_cub *cub);
void d_press(t_cub *cub);
void a_left_press(t_cub *cub);
void a_right_press(t_cub *cub);


#endif