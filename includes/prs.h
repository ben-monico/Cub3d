/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:27:42 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/10 16:51:11 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRS_H
# define PRS_H

# include <fcntl.h>
# include <get_next_line.h>
# include <cub3d.h>

typedef struct s_prs	t_prs;

struct s_prs
{
	char	**file;
	char	**path_to_img;
	char	*floor_c;
	char	*color_c;
};

t_prs		*parsing(void);
int			get_path_img(t_prs *prs);
int			get_colors(char *clr, t_prs *prs);
int			checker_zero(char **map, int y, int x);
void		prs_file(t_prs *prs);
void		clean_parsing(t_prs *data);
void		exit_prs(t_prs *data, int status, char *str);
void		check_portal(char **map, int x, int y);

#endif