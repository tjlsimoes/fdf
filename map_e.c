/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_e.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:37:51 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/24 13:32:56 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_fd_open_array_init(t_fdf *env, char *file_path)
{
	env->file_fd = open(file_path, O_RDONLY);
	if (env->file_fd == -1)
		error_close_window(env, "Unable to open file.");
	env->map->array = (int ***)ft_calloc(1, sizeof(int **) * env->map->height);
	if (!env->map->array)
		error_close_window(env, "Unable to allocate memory for map array.");
}

void	init_cell(int **row, char **split_res, int split_size, int *k)
{
	if (*k < split_size)
	{
		row[*k][0] = ft_atoi(split_res[*k]);
		array_cell_colour_init(split_res[*k], row, k);
	}
	else
		*k += 1;
}

void	row_error_array_free(t_fdf *env, int i, char *line)
{
	free_gnl_static(line, env->file_fd);
	free_map_array_width(env, i, env->map->width);
	close_call_error(env,
		"Error map array row (mrm alloc) and close file.",
		"Unable to allocate memory for map array row,");
}
