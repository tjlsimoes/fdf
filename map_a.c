/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:47:55 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/03 13:21:37 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map_height(t_fdf *env, char *file_path)
{
	int		height;
	char	*line;

	env->file_fd = open(file_path, O_RDONLY);
	if (env->file_fd == -1)
		error_close_window(env, "Unable to open file.", 1);
	height = 0;
	line = get_next_line(env->file_fd);
	while (line)
	{
		free(line);
		line = NULL;
		line = get_next_line(env->file_fd);
		height++;
	}
	free(line);
	line = NULL;
	if (close(env->file_fd) < 0)
		error_close_window(env, "Unable to close file.", 1);
	else if (height == 0)
		error_close_window(env, "Invalid map: zero height.", 1);
	env->map->height = height;
}

// Possible combination of both errors on set_map_height?

void	set_map_width(t_fdf *env, char *file_path)
{
	int		width;
	char	*line;

	env->file_fd = open(file_path, O_RDONLY);
	if (env->file_fd == -1)
		error_close_window(env, "Unable to open file.", 1);
	width = 0;
	line = get_next_line(env->file_fd);
	width = get_nbr_substrings(line, ' ');
	width--;
	check_const_width(env, line, width);
	if (close(env->file_fd) < 0)
		error_close_window(env, "Unable to close file.", 1);
	else if (width == 0)
		error_close_window(env, "Invalid map: zero width initial line.", 1);
	env->map->width = width;
}

// Possible combination of both errors on set_map_height?

// get_map_width() assumes that anything other than spaces between spaces
// on the first line of the map equates to a number.
// Obviously this can not be the case.
// Add a protection further down the road (use of atoi?) in the case
// it is not a number or a pair of numbers (number and colour)?

// get_nbr_substrings(line, ' ') counts the ending \n as a another nbr.
// Hence, width--.

void	initialize_map_array_cell(t_fdf *env, int row_nbr,
									char *line, int width)
{
	char	**values;
	int		k;
	int		**row;

	k = 0;
	row = env->map->array[row_nbr];
	values = ft_split(line, ' ');
	if (!values)
		split_error(env, row_nbr, line);
	while (k < width)
	{
		row[k] = (int *)malloc(sizeof(int) * 2);
		if (!row[k])
		{
			free_gnl_static(line, env->file_fd);
			cell_error_array_free(env, row, row_nbr, k);
			cell_error_split_res_free(values, k, width);
			close_call_error(env,
				"Error array cell init (mem alloc) and file close.",
				"Error array cell init: memory allocation.", 1);
		}
		row[k][0] = ft_atoi(values[k]);
		array_cell_colour_init(line, row, k++); // Check
	}
	free_split_result(values, width);
}

// Possible need to safeguard for ft_atoi(values[]) == 0?

void	initialize_map_array(t_fdf *env, char *file_path)
{
	char	*line;
	int		i;

	i = 0;
	map_fd_open_array_init(env, file_path);
	line = get_next_line(env->file_fd);
	i = 0;
	while (i < env->map->height)
	{
		env->map->array[i] = (int **)ft_calloc(1,
				sizeof(int *) * env->map->width);
		if (!env->map->array[i])
			row_error_array_free(env, i, line);
		initialize_map_array_cell(env, i, line, env->map->width);
		free(line);
		line = NULL;
		line = get_next_line(env->file_fd);
		i++;
	}
	free_gnl_static(line, env->file_fd);
	if (close(env->file_fd) < 0)
		error_close_window(env, "Unable to close file.", 1);
}

void	initialize_map(t_fdf *env, char *file_path)
{
	env->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!env->map)
		error_close_window(env,
			"Unable to allocate memory for map variable.", 1);
	set_map_height(env, file_path);
	set_map_width(env, file_path);
	initialize_map_array(env, file_path);

	// print_array(env); /////////
	// free_map_array_width(env, env->map->height, env->map->width); /////////
	// error_close_window(env, "Mem leak check", 1);
}
