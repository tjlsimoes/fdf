/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:48:58 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/07/23 11:54:17 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./mlx.h"
# include "./mlx_int.h"
# include "X11/X.h"
# include <stdlib.h>
# include <stdio.h>
# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300

typedef struct s_map
{
	int	height;
	int	width;
	int	***array;
	//
}	t_map;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_map	*map;		
}	t_fdf;

#endif