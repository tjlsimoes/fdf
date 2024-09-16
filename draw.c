/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:17:21 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/16 13:08:25 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/// NEED TO UNDERSTAND THIS FUNCTION!
void	img_pix_put(t_fdf *env, int x, int y, int colour)
{
	char	*pixel;
	int		i;

	i = env->bpp - 8;
	pixel = env->data_addr + (y * env->size_line + x * (env->bpp / 8));
	while (i >= 0)
	{
		// big endian: most significant bit is the leftmost bit
		if (env->type != 0)
			*pixel++ = (colour >> i ) & 0xFF;
		// little endian> least significant bit is the lefmost bit
		else
			*pixel++ = (colour >> (env->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

t_point	project(int x, int y, t_fdf *env)
{
	t_point point;
	int	zoom;

	zoom = ft_min(WINDOW_WIDTH / env->map->width / 2,
			WINDOW_HEIGHT / env->map->height / 2);
	point.z = env->map->array[y][x][0];
	
	point.colour = RED_PIXEL;	// Temporary

	point.x = x * zoom;
	point.y = y * zoom;
	point.z *= zoom;
	point.x -= (env->map->width * zoom) / 2;
	point.y -= (env->map->height * zoom) / 2;

	// point.x = x;
	// point.y = y;
	// Isometric projection
	point.x = (x - y) * cos(0.523599);
	point.y = (x + y) * sin(0.523599) - point.z;

	// point.x = (x - y) * 1/ sqrt(2);
	// point.y = (x + y - 2 * point.z) *1/ sqrt(6);

	point.x += WINDOW_WIDTH / 2;
	point.y += (WINDOW_HEIGHT + env->map->height / 2 * zoom) / 2;

	// Try to center.
	// Missing zoom factor.
	// point.x += WINDOW_WIDTH / 2;
	// point.y += WINDOW_HEIGHT / 2;
	return (point);
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
// Need to understand the reason for use of absolute values.

void	draw_map(t_fdf *env)
{
	int y;
	int x;

	y = 0;
	while (y < env->map->height)
	{
		x = 0;
		while (x < env->map->width)
		{
			if (x != env->map->width - 1)
				draw_line(env, project(x, y, env), project(x + 1, y, env));
			if (y != env->map->height - 1)
				draw_line(env, project(x, y, env), project(x, y + 1, env));
			x++;
		}
		y++;
	}	
}

// void	draw_points(t_fdf *env)
// {
// 	int	i;
// 	int j;
// 	int	x_sep;
// 	int y_sep;

// 	x_sep = WINDOW_WIDTH / (env->map->width + 2);
// 	y_sep = WINDOW_HEIGHT / (env->map->height + 2);
// 	i = y_sep;
// 	j = x_sep;
// 	while (i < WINDOW_HEIGHT - y_sep)
// 	{
// 		j = x_sep;
// 		while (j < WINDOW_WIDTH - x_sep)
// 		{
// 			img_pix_put(env, j, i, RED_PIXEL);
// 			j += x_sep;
// 		}
// 		i += y_sep;
// 	}
// }

// void	draw_points(t_fdf *env)
// {
// 	int	i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (i < WINDOW_HEIGHT)
// 	{
// 		j = 0;
// 		while (j < WINDOW_WIDTH)
// 		{
// 			img_pix_put(env, j, i, RED_PIXEL);
// 			j += 60;
// 		}
// 		i += 30;
// 	}
// }

// void	draw_points(t_fdf *env)
// {
// 	img_pix_put(env, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0xFF0000);
// }

int	draw(t_fdf *env)
{
	env->data_addr = NULL;
	env->data_addr = mlx_get_data_addr(env->img, &env->bpp, &env->size_line, 
					&env->type);
	// draw_points(env);
	// render(env);
	draw_map(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

void	render_background(t_fdf *env, int colour)
{
	int	i;
	int	j;

	if (env->win == NULL)
		return ;
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(env, j++, i, colour);
		++i;
	}
}

int	render_rect(t_fdf *env, t_rect rect)
{
	int	i;
	int	j;

	if (env->win == NULL)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(env, j++, i, rect.colour);
		++i;
	}
	return (0);
}

int	render(t_fdf *env)
{
	if (!env->win)
		return (1);
	render_background(env, WHITE_PIXEL);
	render_rect(env, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	render_rect(env, (t_rect){0, 0, 100, 100, RED_PIXEL});
	return (0);
}
