/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:08:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/07 16:30:06 by tjorge-l         ###   ########.fr       */
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

int	ft_atoi_alt(char *nptr)
{
	int		nbr;

	if (!nptr)
		return (0);
	nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		nptr++;
	else if (*nptr == '+')
		nptr++;
	if (*nptr >= '0' && *nptr <= '9')
		nbr = 1;
	return (nbr);
}

void	invalid_first_line(t_fdf *env, char *line)
{
	free_gnl_static(line, env->file_fd);
	if (close(env->file_fd) < 0)
		error_close_window(env, "Unable to close file.");
	error_close_window(env, "Invalid first line.");
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
		{
			free_gnl_static(line, env->file_fd);
			error_close_window(env, "update_width(): split() mem fail.");
		}
		nbr_columns = get_nbr_substrings(line, ' ');
		if (values[nbr_columns - 1][0] == 10)
			nbr_columns--;
		free_split_result(values, get_split_size(values) - 1);
		if (nbr_columns > width && nbr_columns != -1)
			width = nbr_columns;
	}
	line = NULL;
	env->map->width = width;
}

// What would happen if:
//	a) map with nothing is passed.
//	b) map with new line is passed.
//	c) map with regular lines with one in the middle with just a new line.
