/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:47:55 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/07/26 17:45:36 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map_height(t_fdf *env, char *file_path)
{
	int		file_fd;
	int		height;
	char 	*line;

	file_fd = open(file_path, O_RDONLY);
	if (!file_fd)
		error_close_window(env, "Unable to open file.", 1);
	height = 0;
	line = get_next_line(file_fd);
	while (line)
	{
		free(line);
		line = NULL;
		line = get_next_line(file_fd);
		height++;
	}
	free(line);
	line = NULL;
	if (close(file_fd) < 0)
		error_close_window(env, "Unable to close file.", 1);
	else if (height == 0)
		error_close_window(env, "Invalid map: zero height.", 1);
	env->map->height = height;
}

int	get_nbr_substrings(char const *s, char c)
{
	int		i;
	int		k;
	int		count;

	i = 0;
	k = -1;
	count = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c && k > 0)
		{
			k = -1;
		}
		else if (s[i] != c && k < 0)
		{
			k = 1;
			count++;
		}
		i++;
	}
	return (count);
}

void	set_map_width(t_fdf *env, char *file_path)
{
	int		file_fd;
	int		width;
	char 	*line;

	file_fd = open(file_path, O_RDONLY);
	if (!file_fd)
		error_close_window(env, "Unable to open file.", 1);
	width = 0;
	line = get_next_line(file_fd);
	width = get_nbr_substrings(line, ' ');
	width--;
	while (line)
	{
		free(line);
		line = NULL;
		line = get_next_line(file_fd);
	}
	free(line);
	line = NULL;
	if (close(file_fd) < 0)
		error_close_window(env, "Unable to close file.", 1);
	else if (width == 0)
		error_close_window(env, "Invalid map: zero width initial line.", 1);
	env->map->width = width;
}

// get_map_width() assumes that anything other than spaces between spaces
// on the first line of the map equates to a number.
// Obviously this can not be the case.
// Add a protection further down the road (use of atoi?) in the case
// it is not a number or a pair of numbers (number and colour)?

// get_nbr_substrings(line, ' ') counts the ending \n as a another nbr.
// Hence, width--.

void	initialize_map(t_fdf *env, char *file_path)
{
	
	env->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!env->map)
		error_close_window(env, "Unable to allocate memory for map variable.", 1);
	set_map_height(env, file_path);
	set_map_width(env, file_path);

	error_close_window(env, "Mem leak check", 1);
		
}