#ifndef IMG_H
# define IMG_H

# include <cub3d.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		get_color_img(t_data *data, int x, int y);
void	add_sprite(t_data *data, int x, int y, int color);

#endif