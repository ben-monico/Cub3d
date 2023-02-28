#include <cub3d.h>

void	add_sprite(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (color == COLOR_TRANSPARENT || (x >= screenW || y >= screenH))
		return ;
	dst = (data->addr + (y * data->size_line + x * (data->bpp / 8)));
	*(unsigned int*)dst = color;
}

void	destroy_sprite(t_sprite *sprite)
{
	if (!sprite)
		return ;
	mlx_destroy_image(new_cube()->mlx, sprite->img);
	free_ob(sprite);
}