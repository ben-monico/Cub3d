/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:57:00 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/12 01:48:07 by bcarreir         ###   ########.fr       */
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
# include <prs.h>
# include <structs.h>
# include <defines.h>
# include <math.h>

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			add_sprite(t_data *data, int x, int y, int color);
void			put_image_to_window(t_data *img, char *file, int x, int y);
void			put_png(t_data *img, int offsetW, int offsetH, int chroma_max);
unsigned int	get_color_img(t_data *data, int x, int y);
void			new_minimap(t_cub *cub, char **mtx, double iter);

// Cube Utils
t_cub			*cube(void);
void			ft_screens(int i);
void			init_screens(t_cub *cub);
void			screen_sprite_cmp(t_cub *cub, char **mtx);
void			load_img(t_cub *data, char **path);
void			create_cube(t_cub *cub);
int				press_key(int key, t_cub *cub);
void			easter_egg(t_cub *data);

// Raycastin Utils
void			raycasting(t_cub *cub);
void			init_player_vars(t_cub *cub);
void			init_screen_images(t_cub *cub);
void			get_textures(t_cub *cub, int start, int end);
void			get_wall_texture(t_cub *data, t_rcast *dst);

// Rendering Utils
void			render_screen(t_cub *cub);
double			calculate_y(t_data *line, float i);
void			set_line_color(int c, t_cub *cub, t_rcast *rcast, float wallx);

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
int				portal_teleport(t_cub *cub, char **mtx, double x, double y);
int				mouse_move(int x, int y, t_cub *cub);
void			p_rotation(t_player *player, double angle);
void			w_press(t_cub *cub);
void			a_press(t_cub *cub);
void			s_press(t_cub *cub);
void			d_press(t_cub *cub);
void			arrow_left_press(t_cub *cub);
void			arrow_right_press(t_cub *cub);

#endif