/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:08:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/08/01 13:40:15 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	split_error(t_fdf *env, int row_nbr, char *line)
{
	// while(k <= width + 1)	// Three lines for testing purposes.
		// 	free(values[k++]);
	// free(values);
	free_gnl_static(line, env->file_fd);
	free_map_array_width(env, ++row_nbr, env->map->width);
	if (close(env->file_fd) < 0)
			error_close_window(env, "Error on initializing map array row - unable to allocate memory to split() - and on closing file.", 1);
	error_close_window(env, "Error on initializing map array row: unable to allocate memory to split().", 1);
}

void	cell_error_array_free(t_fdf *env, int **row, int row_nbr, int k)
{
		free_map_array_row(row, k);
		free_map_array_width(env, row_nbr, env->map->width);
}

void	cell_error_split_res_free(char	**values, int k, int width)
{
	while(k <= width)
		free(values[k++]);
	free(values);
}

void	close_call_error(t_fdf *env, char *close_error_msg, char *error_msg, int sys_error)
{
	if (close(env->file_fd) < 0)
		error_close_window(env, close_error_msg, sys_error);
	error_close_window(env, error_msg, sys_error);
}

void	array_cell_colour_init(char *line, int **row, int k)
{
	if (ft_strchr(line, ','))
		row[k][1] = ft_atoi(ft_strchr(line, ',') + 1);
	// else
		// Set default colour?
}

void	initialize_map_array_cell(t_fdf *env, int row_nbr, char *line, int width)
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
			close_call_error(env,"Error on initializing map array cell - unable to allocate memory - and on closing file.", "Error on initializing map array cell: unable to allocate memory .", 1);
		}
		row[k][0] = ft_atoi(values[k]);
		array_cell_colour_init(line, row, k);
		k++;
	}
	free_split_result(values, width);
}

// Possible need to safeguard for ft_atoi(values[]) == 0?

void	initialize_map_array(t_fdf *env, char *file_path)
{
	char 	*line;
	int		height;
	int		i;

	i = 0;
	height = env->map->height;
	env->file_fd = open(file_path, O_RDONLY);
	if (!env->file_fd)
		error_close_window(env, "Unable to open file.", 1);

	env->map->array = (int ***)ft_calloc(1, sizeof(int **) * env->map->height);
	if (!env->map->array)
		error_close_window(env, "Unable to allocate memory for map array.", 1);

	line = get_next_line(env->file_fd);
	i = 0;
	while (i < height)
	{
		env->map->array[i] = (int **)ft_calloc(1, sizeof(int *) * env->map->width);
		if (!env->map->array[i])
		{
			free_map_array_width(env, i, env->map->width);
			free_gnl_static(line, env->file_fd);
			if (close(env->file_fd) < 0)
				error_close_window(env, "Unable to allocate memory for map array row and close file.", 1);
			error_close_window(env, "Unable to allocate memory for map array row", 1);
		}
		ft_printf("Row %d\n", i);
		initialize_map_array_cell(env, i, line, env->map->width);
		free(line);
		line = NULL;
		line = get_next_line(env->file_fd);
		i++;
	}
	free(line);
	line = NULL;

	if (close(env->file_fd) < 0) //
		error_close_window(env, "Unable to close file.", 1);
}
