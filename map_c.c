/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:08:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/23 11:22:53 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	int	nbr_columns;

	difference_q = 0;
	while (line)
	{
		free(line);
		line = NULL;
		line = get_next_line(env->file_fd);
		nbr_columns = get_nbr_substrings(line, ' ') - 1;
		if (width != nbr_columns && nbr_columns != -1)
			difference_q = 1;
	}
	free(line);
	line = NULL;
	if (difference_q)
		error_close_window(env, "Invalid map: lines with unequal width.");
}

// What would happen if:
//	a) map with nothing is passed.
//	b) map with new line is passed.
//	c) map with regular lines with one in the middle with just a new line.
