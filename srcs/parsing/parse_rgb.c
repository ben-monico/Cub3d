/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:34:37 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/10 16:43:41 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <prs.h>

int	rgb_util(char *clr, t_prs *prs)
{
	int	n;
	int	i;

	i = 0;
	while (clr[i])
	{
		if (clr[i] != ',' && !string().isdig(clr[i]))
		{
			clean_parsing(prs);
			exit_free(cube(), 1, "Not a recognizable RGB range systemO");
		}
		i++;
	}
	n = string().atoi(clr);
	if (n > 255 || n < 0)
	{
		clean_parsing(prs);
		exit_free(cube(), 1, "Out of RGB range");
	}
	return (n);
}

int	get_colors(char *clr, t_prs *prs)
{
	int	i;
	int	ct;
	int	rgb[3];

	ct = 0;
	i = -1;
	while (clr && clr[++i])
		if (clr[i] == ',')
			ct++;
	if (!clr || ct != 2)
		exit_prs(prs, 1, "Wrong amount of RGB fields");
	while (string().ft_isspace(*clr))
		clr++;
	i = -1;
	while (++i < 3)
	{
		rgb[i] = rgb_util(clr, prs);
		while (*clr && *clr != ',')
			clr++;
		if (*clr == ',')
			clr++;
	}
	i = 255;
	return (i << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
