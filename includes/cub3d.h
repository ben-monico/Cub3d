/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/06 16:10:15 by bcarreir         ###   ########.fr       */
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
# include <structs.h>
# include <defines.h>
# include <math.h>



void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	add_sprite(t_data *data, int x, int y, int color);
void	put_image_to_window(t_sprite *spr, char	*file,  int x, int y);
unsigned int	get_color_img(t_data *data, int x, int y);
unsigned int	get_color_wall(t_wall data, int x, int y);


t_cub	*new_cube(void);
// Mlx Utils
void	load_img(t_cub *data, char **path);
void	create_cube(t_cub *cub);
int		press_key(int key, t_cub *cub);

// Raycastin Utils
void    raycasting(t_cub *cub);
void	init_raycast_vars(t_cub *cub);
void	get_textures(t_cub *cub, int start, int end);
void	get_wall_texture(t_cub *data, t_dist *dst);

// Rendering Utils
void	render_screen(t_cub *cub);

// Rendering Utils
void	render_screen(t_cub *cub);

// Read File and Create Map
int		read_file(t_cub *cube, char *file_name, int ac);
void	read_map(t_cub *cube);
void	check_map_elements(t_cub *cub);

// Clean and Exit Program
void	exit_free(t_cub *data, int status, char *str);
int		exit_win(t_cub *cub);
int		free_ob(void *v);
int		close_window(t_cub *vars);

// Parsing Resources
int		get_map(char **file, t_cub *cube);

// Moving
void    verify_collision_and_door(t_cub *cub, double x, double y);
int		mouse_move(int x, int y, t_cub *cub);
void	p_rotation(t_player *player, double angle);
void	w_press(t_cub *cub);
void	a_press(t_cub *cub);
void	s_press(t_cub *cub);
void	d_press(t_cub *cub);
void	arrow_left_press(t_cub *cub);
void	arrow_right_press(t_cub *cub);



#endif