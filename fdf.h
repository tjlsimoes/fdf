/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:48:58 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/24 12:46:30 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "math.h"
# include "libft/libft.h"
# include "printf/ft_printf.h"
# include "./mlx.h"
# include "./mlx_int.h"
# include "X11/X.h"
# include <stdlib.h>
# include <stdio.h>
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define RED 0xFF0000

typedef struct s_camera
{
	int		zoom;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	int		x_offset;
	int		y_offset;
	int		iso;
}				t_camera;

typedef struct s_map
{
	int	height;
	int	width;
	int	***array;
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
	void		*img;
	char		*data_addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			type;
	t_camera	*camera;
}	t_fdf;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	colour;
}	t_point;

// Error handling
void	error(char *error_msg);
void	error_close_window(t_fdf *env, char *error_msg);

// Environment initialization
t_fdf	*initialize_env(char *str);
void	initialize_camera(t_fdf *env);

int		close_window(t_fdf *env);
void	free_display_env(t_fdf *env);
void	img_free(t_alt_img *img);
void	error_img_close_window(t_fdf *env);
char	*set_title(t_fdf *env, char *str);

// Map initialization
void	initialize_map(t_fdf *env, char *file_path);
void	initialize_map_array(t_fdf *env, char *file_path);
void	initialize_map_array_cell(t_fdf *env, int row_nbr,
			char *line, int width);

void	set_map_height(t_fdf *env, char *file_path);
void	set_map_width(t_fdf *env, char *file_path);

void	free_map_array_width(t_fdf *env, int i, int width);
void	free_map_array_row(int **row, int i);
void	free_gnl_static(char *line, int file_fd);
void	free_split_result(char **values, int width);
// void	print_array(t_fdf *env);

int		get_nbr_substrings(char const *s, char c);
void	update_width(t_fdf *env, char *line, int width);
void	check_const_width(t_fdf *env, char *line, int width);

void	split_error(t_fdf *env, int row_nbr, char *line);
void	cell_error_array_free(t_fdf *env, int **row, int row_nbr, int k);
void	cell_error_split_res_free(char	**values, int k, int width);
void	close_call_error(t_fdf *env, char *close_error_msg,
			char *error_msg);
int		ft_atoi_rgb(char *str, int str_base);
void	array_cell_colour_init(char *cell, int **row, int *k);

void	map_fd_open_array_init(t_fdf *env, char *file_path);
void	row_error_array_free(t_fdf *env, int i, char *line);

// Drawing
int		draw(t_fdf *env);

void	img_pix_put(t_fdf *env, int x, int y, int colour);
void	draw_map(t_fdf *env);
void	draw_line(t_fdf *env, t_point a, t_point b);

void	rotate_x(int *y, int *z, double x_angle);
void	rotate_y(int *x, int *z, double y_angle);
void	rotate_z(int *x, int *y, double z_angle);

t_point	project(int x, int y, t_fdf *env);

// Line Algorithm
void	slope_less_than_one(t_fdf *env, t_point a, t_point b);
void	slope_bigger_than_one(t_fdf *env, t_point a, t_point b);
void	update_x(t_point *a, int dif);
void	update_y(t_point *a, int dif);

// Hook handling
void	set_hooks(t_fdf *env);
int		handle_mouse_click(int button, int x, int y, void *params);
int		handle_keypress(int keysym, void *params);
void	change_angle(int keysym, t_fdf *env);
void	zoom(int button, t_fdf *env);
void	translate(int keycode, t_fdf *env);
void	switch_projection(t_fdf *env);
void	reset(t_fdf *env);

#endif