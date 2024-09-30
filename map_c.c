/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:08:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/30 13:55:34 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_split_size(char **split_result)
{
	int	i;

	i = 0;
	if (!split_result)
		return (i);
	while (split_result[i])
		i++;
	return (i);
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

void	update_width(t_fdf *env, char *line, int width)
{
	int		nbr_columns;
	char	**values;

	while (line)
	{
		free(line);
		line = NULL;
		line = get_next_line(env->file_fd);
		if (!line)
			break ;
		values = ft_split(line, ' ');
		if (!values)
			error_close_window(env, "update_width(): split() mem fail.");
		nbr_columns = get_nbr_substrings(line, ' ');
		if (values[nbr_columns - 1][0] == 12)
			nbr_columns--;
		free_split_result(values, get_split_size(values) - 1);
		if (nbr_columns > width && nbr_columns != -1)
			width = nbr_columns;
	}
	free(line);
	line = NULL;
	env->map->width = width;
}

// What would happen if:
//	a) map with nothing is passed.
//	b) map with new line is passed.
//	c) map with regular lines with one in the middle with just a new line.
