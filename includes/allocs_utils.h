/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocs_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmonico <benmonico@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:03:39 by mgranate          #+#    #+#             */
/*   Updated: 2023/02/15 20:46:26 by benmonico        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCS_UTILS_H
# define ALLOCS_UTILS_H

# include <stdlib.h>
# include "allocs.h"

void		free_matrix(void **matrix);
void		free_array(void *array);
void		*ft_calloc(size_t size);

#endif