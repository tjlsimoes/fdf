/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:48:58 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/03 16:43:04 by tjorge-l         ###   ########.fr       */
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

typedef struct s_alt_img
{
	t_img	*img_ptr;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_alt_img;

typedef struct s_fdf
{
	int			file_fd;
	void		*mlx;
	void		*win;
	t_map		*map;
	t_img		*img;
}	t_fdf;

// Error handling
void	ft_error(char *error_msg, int sys_error);
void	error_close_window(t_fdf *env, char *error_msg, int sys_error);

// Environment initialization
t_fdf	*initialize_env(char *str);

int		close_window(t_fdf *env);
void	free_display_env(t_fdf *env);
void	img_free(t_alt_img *img);
void	error_img_close_window(t_fdf *env, char *error_msg, int sys_error);
char	*set_title(t_fdf *env, char *str);

// Map initialization
void	initialize_map(t_fdf *env, char *file_path);
void	initialize_map_array(t_fdf *env, char *file_path);
void	initialize_map_array_cell(t_fdf *env, int row_nbr, char *line, int width);

void	set_map_height(t_fdf *env, char *file_path);
void	set_map_width(t_fdf *env, char *file_path);

void	free_map_array_width(t_fdf *env, int i, int width);
void	free_map_array_row(int **row, int i);
void	free_gnl_static(char *line, int file_fd);
void	free_split_result(char **values, int width);
void	print_array(t_fdf *env);

int		get_nbr_substrings(char const *s, char c);
void	check_const_width(t_fdf *env, char *line, int width);

void	split_error(t_fdf *env, int row_nbr, char *line);
void	cell_error_array_free(t_fdf *env, int **row, int row_nbr, int k);
void	cell_error_split_res_free(char	**values, int k, int width);
void	close_call_error(t_fdf *env, char *close_error_msg, char *error_msg, int sys_error);
void	array_cell_colour_init(char *line, int **row, int k);

void	map_fd_open_array_init(t_fdf *env, char *file_path);
void	row_error_array_free(t_fdf *env, int i, char *line);

// Drawing
void	draw(t_fdf *env);

void	img_pix_put(t_img *img, int x, int y, int colour);
void	draw_points(t_fdf *env);

	//Temporary
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0xFF00
# define WHITE_PIXEL 0xFFFFFF

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int	height;
	int colour;
}	t_rect;

int		render(t_fdf *env);
void	render_background(t_fdf *env, int colour);
int		render_rect(t_fdf *env, t_rect rect);

// Hook handling
void	set_hooks(t_fdf *env);
int		handle_no_event();
int		handle_mouse_click(int button, int x, int y);
int		handle_keypress(int keysym, t_fdf *env);

#endif