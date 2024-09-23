/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:17:21 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/23 10:47:04 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	draw(t_fdf *env)
{
	env->data_addr = NULL;
	env->data_addr = mlx_get_data_addr(env->img, &env->bpp, &env->size_line,
			&env->type);
	ft_bzero(env->data_addr, WINDOW_WIDTH * WINDOW_HEIGHT * (env->bpp / 8));
	draw_map(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

void	draw_map(t_fdf *env)
{
	int	y;
	int	x;

	y = 0;
	if (env->camera->x_angle > 0)
		y = env->map->height - 1;
	while (y < env->map->height && y >= 0)
	{
		x = 0;
		if (env->camera->y_angle > 0)
			x = env->map->width - 1;
		while (x < env->map->width && x >= 0)
		{
			if (x != env->map->width - 1)
				draw_line(env, project(x, y, env), project(x + 1, y, env));
			if (y != env->map->height - 1)
				draw_line(env, project(x, y, env), project(x, y + 1, env));
			x += -2 * (env->camera->y_angle > 0) + 1;
		}
		y += -2 * (env->camera->x_angle > 0) + 1;
	}
}

void	draw_line(t_fdf *env, t_point a, t_point b)
{
	int	dy;
	int	dx;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (abs(dx) > abs(dy))
		slope_less_than_one(env, a, b);
	else
		slope_bigger_than_one(env, a, b);
}
