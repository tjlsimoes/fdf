/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:04:12 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/23 11:27:47 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *env)
{
	free_map_array_width(env, env->map->height, env->map->width);
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	free(env->map);
	free(env->camera);
	free(env);
	exit(0);
}

void	free_display_env(t_fdf *env)
{
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	free(env);
}

void	img_free(t_alt_img *img)
{
	free(img->data_addr);
	free(img);
}

void	error_img_close_window(t_fdf *env)
{
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	free(env);
	ft_putstr_fd("Unable to create image.", 2);
}

char	*set_title(t_fdf *env, char *str)
{
	char	*title;

	title = ft_strjoin(ft_strdup("FDF - "), str);
	if (!title)
	{
		free_display_env(env);
		ft_putstr_fd("Unable to allocate memory for title.", 2);
	}
	return (title);
}
