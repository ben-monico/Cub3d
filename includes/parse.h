/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:27:42 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/08 19:37:34 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <fcntl.h>
# include <get_next_line.h>
# include <cub3d.h>

typedef struct s_parse	t_parse;

struct s_parse
{
	char	**file;
	char	**path_to_img;
	char	*f_c;
	char	*c_c;
};

t_parse		*parsing(void);
int			get_path_img(t_parse *parse);
int			get_colors(char *clr, t_parse *parse);
int			checker_zero(char **map, int y, int x);
void		parse_file(t_parse *parse);
void		clean_parsing(t_parse *data);
void		exit_parse(t_parse *data, int status, char *str);
void		check_portal(char **map, int x, int y);

#endif