/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:23:30 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/24 13:00:25 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	split_error(t_fdf *env, int row_nbr, char *line)
{
	free_gnl_static(line, env->file_fd);
	free_map_array_width(env, ++row_nbr, env->map->width);
	if (close(env->file_fd) < 0)
		error_close_window(env,
			"Error array row init (split() mem alloc) and file close.");
	error_close_window(env, "Error array row init: split() mem alloc.");
}

// Three lines used for testing purposes of split_error.
// while(k <= width + 1)
	// 	free(values[k++]);
// free(values);

void	cell_error_array_free(t_fdf *env, int **row, int row_nbr, int k)
{
	free_map_array_row(row, k);
	free_map_array_width(env, row_nbr, env->map->width);
}

void	cell_error_split_res_free(char	**values, int k, int width)
{
	while (k <= width)
		free(values[k++]);
	free(values);
}

void	close_call_error(t_fdf *env,
		char *close_error_msg, char *error_msg)
{
	if (close(env->file_fd) < 0)
		error_close_window(env, close_error_msg);
	error_close_window(env, error_msg);
}

void	array_cell_colour_init(char *cell, int **row, int *k)
{
	if (ft_strchr(cell, ','))
		row[*k][1] = ft_atoi_rgb(ft_strchr(cell, ',') + 1, 16);
	else
		row[*k][1] = RED;
	*k += 1;
}
