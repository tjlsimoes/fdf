/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:47:55 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/30 13:29:09 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map_height(t_fdf *env, char *file_path)
{
	int		height;
	char	*line;

	env->file_fd = open(file_path, O_RDONLY);
	if (env->file_fd == -1)
		error_close_window(env, "Unable to open file.");
	height = 0;
	line = get_next_line(env->file_fd);
	if (!line || !ft_isalnum(line[0]))
		error_close_window(env, "Invalid first line.");
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
		error_close_window(env, "Unable to close file.");
	else if (height == 0)
		error_close_window(env, "Invalid map: zero height.");
	env->map->height = height;
}

// Possible combination of both errors on set_map_height?

void	set_map_width(t_fdf *env, char *file_path)
{
	int		width;
	char	*line;
	char	**values;

	env->file_fd = open(file_path, O_RDONLY);
	if (env->file_fd == -1)
		error_close_window(env, "Unable to open file.");
	width = 0;
	line = get_next_line(env->file_fd);
	values = ft_split(line, ' ');
	if (!values)
		error_close_window(env, "Error set_map_width(): split() mem fail.");
	width = get_nbr_substrings(line, ' ');
	if (values[width - 1][0] == 12)
		width--;
	free_split_result(values, get_split_size(values) - 1);
	update_width(env, line, width);
	if (close(env->file_fd) < 0)
		error_close_window(env, "Unable to close file.");
	else if (width <= 1)
		error_close_window(env, "Invalid map: invalid width.");
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
	int		split_size;

	k = 0;
	row = env->map->array[row_nbr];
	values = ft_split(line, ' ');
	if (!values)
		split_error(env, row_nbr, line);
	split_size = get_split_size(values);
	while (k < width)
	{
		row[k] = (int *)ft_calloc(1, sizeof(int) * 2);
		if (!row[k])
		{
			free_gnl_split(line, env, --split_size, values);
			cell_error_array_free(env, row, row_nbr, k);
			close_call_error(env,
				"Error array cell init: mem alloc and file close.",
				"Error array cell init: memory allocation.");
		}
		init_cell(row, values, split_size, &k);
	}
	free_split_result(values, --split_size);
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
	{
		free_map_array_width(env, env->map->height, env->map->width);
		error_close_window(env, "Unable to close file.");
	}
}

void	initialize_map(t_fdf *env, char *file_path)
{
	env->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!env->map)
		error_close_window(env,
			"Unable to allocate memory for map variable.");
	set_map_height(env, file_path);
	set_map_width(env, file_path);
	initialize_map_array(env, file_path);
}
