/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:23:30 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/08/02 12:27:27 by tjorge-l         ###   ########.fr       */
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
