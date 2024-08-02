/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_e.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:37:51 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/08/02 12:43:20 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_fd_open_array_init(t_fdf *env, char *file_path)
{
	env->file_fd = open(file_path, O_RDONLY);
	if (!env->file_fd)
		error_close_window(env, "Unable to open file.", 1);
	env->map->array = (int ***)ft_calloc(1, sizeof(int **) * env->map->height);
	if (!env->map->array)
		error_close_window(env, "Unable to allocate memory for map array.", 1);
}

void	row_error_array_free(t_fdf *env, int i, char *line)
{
	free_gnl_static(line, env->file_fd);
	free_map_array_width(env, i, env->map->width);
	close_call_error(env,"Unable to allocate memory for map array row and close file.", "Unable to allocate memory for map array row,", 1);
}
