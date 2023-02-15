/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:02:04 by mgranate          #+#    #+#             */
/*   Updated: 2023/02/15 17:03:59 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCS_H
# define ALLOCS_H

# include <stdlib.h>

typedef struct s_allocs		t_allocs;

struct s_allocs
{
	void	*(*calloc)(size_t size);
	void	(*free_matrix)(void **matrix);
	void	(*free_array)(void *array);
};

t_allocs	alloc(void);

#endif