/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:07:24 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/08/02 12:27:52 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	free_split_result(char **values, int width)
{
	int	i;

	i = 0;
	while (i <= width)
		free(values[i++]);
	free(values);
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
