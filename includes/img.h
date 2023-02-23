/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 01:59:33 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/23 22:29:53 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

# include <cub3d.h>

typedef struct s_sprite	t_sprite;
typedef struct s_data	t_data;

struct		s_data
{
	void	*ptr;
	char	*addr;		// In my code I changed this to int *, which I will explain in a second
	int		bpp;	//when using ARGB this value is always 32
	int		size_line;	//This value represents (your image width) * 4 which I will also explain after
	int		endian;		//This value can be either 0 or 1 and will indicate how the ARGB bytes are organized (from front to back or back to front)
	int		width;
	int		height;
};

struct s_sprite
{
	void		*img;
	t_data		data;
};

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	add_sprite(t_data *data, int x, int y, int color);
void	put_image_to_window(t_sprite *spr, char	*file,  int x, int y);

#endif