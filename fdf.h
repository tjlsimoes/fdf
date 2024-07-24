/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:48:58 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/07/24 11:28:23 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
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


void	ft_error(char *error_msg, int sys_error);

t_fdf	*initialize_env(char *str);

int		close_window(t_fdf *env);

void	set_hooks(t_fdf *env);
int		handle_no_event();
int		handle_mouse_click(int button, int x, int y);
int		handle_keypress(int keysym, t_fdf *env);

#endif