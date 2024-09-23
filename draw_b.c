/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:17:21 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/23 10:46:21 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_fdf *env, int x, int y, int colour)
{
	char	*pixel;
	int		i;

	if (!(x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT))
		return ;
	i = env->bpp - 8;
	pixel = env->data_addr + (y * env->size_line + x * (env->bpp / 8));
	while (i >= 0)
	{
		if (env->type != 0)
			*pixel++ = (colour >> i) & 0xFF;
		else
			*pixel++ = (colour >> (env->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
// Big endian (Most significant bit is the lefmost bit) if env.type != 0
// Little endian (Less significant bit is the lefmost bit) if env.type == 0

void	rotate_x(int *y, int *z, double x_angle)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(x_angle) + *z * sin(x_angle);
	*z = prev_y * -sin(x_angle) + *z * cos(x_angle);
}

void	rotate_y(int *x, int *z, double y_angle)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(y_angle) + *z * sin(y_angle);
	*z = prev_x * -sin(y_angle) + *z * cos(y_angle);
}

void	rotate_z(int *x, int *y, double z_angle)
{
	t_point	prev;

	prev.x = *x;
	prev.y = *y;
	*x = prev.x * cos(z_angle) - prev.y * sin(z_angle);
	*y = prev.x * sin(z_angle) + prev.y * cos(z_angle);
}

t_point	project(int x, int y, t_fdf *env)
{
	t_point	point;

	point.z = env->map->array[y][x][0];
	point.colour = env->map->array[y][x][1];
	point.x = x * env->camera->zoom;
	point.y = y * env->camera->zoom;
	point.z *= env->camera->zoom / env->camera->z_height;
	point.x -= (env->map->width * env->camera->zoom) / 2;
	point.y -= (env->map->height * env->camera->zoom) / 2;
	rotate_x(&point.y, &point.z, env->camera->x_angle);
	rotate_y(&point.x, &point.z, env->camera->y_angle);
	rotate_z(&point.x, &point.y, env->camera->z_angle);
	point.x += WINDOW_WIDTH / 2 + env->camera->x_offset;
	point.y += (WINDOW_HEIGHT + env->map->height / 2 * env->camera->zoom) / 2
		+ env->camera->y_offset;
	return (point);
}
