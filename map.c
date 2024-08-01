/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:47:55 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/08/01 13:00:48 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map_height(t_fdf *env, char *file_path)
{
	int		height;
	char 	*line;

	env->file_fd = open(file_path, O_RDONLY);
	if (!env->file_fd)
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

void	check_const_width(t_fdf *env, char *line, int width)
{
	int	difference_q;
	int nbr_columns;

	difference_q = 0;
	while (line)
	{
		free(line);
		line = NULL;
		line = get_next_line(env->file_fd);
		nbr_columns = get_nbr_substrings(line, ' ') - 1;
		if (width != nbr_columns && nbr_columns != - 1)
			difference_q = 1;
	}
	free(line);
	line = NULL;
	if (difference_q)
		error_close_window(env, "Invalid map: lines with unequal width.", 1);
}

// What would happen if:
//	a) map with nothing is passed.
//	b) map with new line is passed.
//	c) map with regular lines with one in the middle with just a new line.

void	set_map_width(t_fdf *env, char *file_path)
{
	int		width;
	char 	*line;

	env->file_fd = open(file_path, O_RDONLY);
	if (!env->file_fd)
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

void	free_map_array_width(t_fdf *env, int i, int width)
{
	int	j;
	int	k;

	j = 0;
	while (j < i)
	{
		k = 0;
		while (k < width)
		{
			free(env->map->array[j][k]);
			k++;
		}
		free(env->map->array[j]);
		j++;
	}
	free(env->map->array);
}

void	free_map_array_row(int **row, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(row[j]);
		j++;
	}
	free(row);
}

// free_map_array() is assuming that there's only a need
// to free array rows up to i and not including i. As from
// it is being called precisely when row i mem alloc fails.

void	free_gnl_static(char *line, int file_fd)
{
	while (line)
	{
		free(line);
		line = NULL;
		line = get_next_line(file_fd);
	}
	free(line);
	line = NULL;
}

void	print_array(t_fdf *env)
{
	int i;
	int	j;
	
	i = 0;
	while(i < env->map->height)
	{
		j = 0;
		while (j < env->map->width)
		{
			ft_printf("%d ", env->map->array[i][j][0]);
			j++;
		}
		i++;
		ft_printf("\n'");
	}
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
	while (k < width)
	{
		row[k] = (int *)malloc(sizeof(int) * 2);
		if (!row[k])
		{
			free_gnl_static(line, env->file_fd);
			free_map_array_row(row, k);
			free_map_array_width(env, row_nbr, env->map->width);
			while(k <= width)
				free(values[k++]);
			free(values);
			if (close(env->file_fd) < 0)
				error_close_window(env, "Error on initializing map array cell - unable to allocate memory - and on closing file.", 1);
			error_close_window(env, "Error on initializing map array cell: unable to allocate memory .", 1);
		}
		row[k][0] = ft_atoi(values[k]);
		// Shouldn't there be a safeguard here in case
		// ft_atoi(values[i]) returns the default 0?
		if (ft_strchr(line, ','))
			row[k][1] = ft_atoi(ft_strchr(line, ',') + 1);
			// Safeguard for possibility of 
			// ft_atoi(ft_strchr(line, ',') + 1) == 0
		// else
			// Set default colour?
		free(values[k]);
		k++;
	}
	free(values[k]);
	free(values);
}

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

void	initialize_map(t_fdf *env, char *file_path)
{
	env->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!env->map)
		error_close_window(env, "Unable to allocate memory for map variable.", 1);
	set_map_height(env, file_path);
	set_map_width(env, file_path);
	initialize_map_array(env, file_path);

	print_array(env); /////////
	free_map_array_width(env, env->map->height, env->map->width); /////////
	error_close_window(env, "Mem leak check", 1);
		
}