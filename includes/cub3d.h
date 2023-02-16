/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmonico <benmonico@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:19 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/16 18:59:23 by benmonico        ###   ########.fr       */
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

# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_KEY_EXIT			17


# if MACKEYMAP==1
#  define KEY_ESC	53
#  define KEY_W		13
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define LEFT 		123
#  define RIGHT 	124
# else
#  define KEY_ESC	65307
#  define W 			119
#  define A 			97
#  define S 			115
#  define D 			100
#  define LEFT 		65361
#  define RIGHT 		65363
# endif

typedef struct s_g t_g;

struct s_g
{
    void	*mlx;
	void    *win;
    int     **map_mtx;  
};

typedef struct		s_img
{
	void	*ptr;
	char	*addr;		// In my code I changed this to int *, which I will explain in a second
	int		bpp;	//when using ARGB this value is always 32
	int		size_line;	//This value represents (your image width) * 4 which I will also explain after
	int		endian;		//This value can be either 0 or 1 and will indicate how the ARGB bytes are organized (from front to back or back to front)
}			t_img;

#endif