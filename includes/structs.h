/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:55:20 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/08 22:24:04 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_sprite	t_sprite;
typedef struct s_data	t_data;
typedef struct s_cub	t_cub;
typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_dist	t_dist;
typedef struct s_img	t_img;

struct		s_data
{
	void	*ptr;
	char	*addr;
	int		bpp;	
	int		size_line;	
	int		endian;		
	int		width;
	int		height;
	int		ceilingpoint;
	int		floorpoint;
	double	wall_height;
	int		x;
};

struct		s_img
{
	int		colors[2];
	char	**path;
	t_data	wall[5];
};

struct s_sprite
{
	void		*img;
	t_data		data;
};

struct s_dist
{
	double	raydir_y;
	double	raydir_x;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	fisheye;
	double	wallx;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		wallside_x;
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
	double	pos_x;
	double	pos_y;
	double	dir_y;
	double	dir_x;
	double	fov_x;
	double	fov_y;
	char	obj_hit;
	int		can_open;
};

struct s_cub
{
	void		*mlx;
	void		*win;
	int			**map_mtx;
	t_data		render_img;
	t_data		sprites[3];
	t_map		map;
	t_img		img;
	t_player	player;
};

#endif