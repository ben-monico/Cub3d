/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:59:14 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/03 03:16:23 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H


# define screenW				1280
# define screenH				720
# define SIZE_X					64
# define SIZE_Y					64
# define COLOR_TRANSPARENT 		0xd411aa
# define DUB_STEP				0.1

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

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
#  define ARROW_UP 		65362
#  define ARROW_DOWN 	65364
#  define ARROW_LEFT 	65361
#  define ARROW_RIGHT	65363
#  endif

#endif