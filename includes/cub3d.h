/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/08 18:25:52 by bcarreir         ###   ########.fr       */
=======
/*   Updated: 2023/03/08 22:17:54 by mgranate_ls      ###   ########.fr       */
>>>>>>> 26bd9c3326026bdd0592044b4e0146f4de632c9e
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

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			add_sprite(t_data *data, int x, int y, int color);
void			put_image_to_window(t_data *img, char *file, int x, int y);
void			put_image_remove_chroma(t_data *img, int offsetW, int offsetH, \
					int chroma_max);
unsigned int	get_color_img(t_data *data, int x, int y);

// Cube Utils
t_cub			*new_cube(void);
void			load_img(t_cub *data, char **path);
void			create_cube(t_cub *cub);
int				press_key(int key, t_cub *cub);

// Raycastin Utils
void			raycasting(t_cub *cub);
void			init_raycast_vars(t_cub *cub);
void			get_textures(t_cub *cub, int start, int end);
void			get_wall_texture(t_cub *data, t_dist *dst);

// Rendering Utils
void			render_screen(t_cub *cub);
void			set_line_color(t_cub *cub, t_dist *dist, float wallx);

// Read File and Create Map
int				read_file(t_cub *cube, char *file_name, int ac);
void			read_map(t_cub *cube);
void			check_map_elements(t_cub *cub);
void			read_aux(t_cub *cub, t_map *map, int x, int y);
int				check_zero1(t_map *map, char c, int y, int x);

// Clean and Exit Program
void			exit_free(t_cub *data, int status, char *str);
int				close_window(t_cub *vars);

// Parsing Resources
int				get_map(char **file, t_cub *cube);

// Moving
void			verify_collision_and_door(double x, double y);
void			open_portal(t_cub *cub);
int				mouse_move(int x, int y, t_cub *cub);
void			p_rotation(t_player *player, double angle);
void			w_press(t_cub *cub);
void			a_press(t_cub *cub);
void			s_press(t_cub *cub);
void			d_press(t_cub *cub);
void			arrow_left_press(t_cub *cub);
void			arrow_right_press(t_cub *cub);

#endif