/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:17:21 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/04 11:20:56 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	draw_points(t_fdf *env)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(env, j, i, RED_PIXEL);
			j += 60;
		}
		i += 30;
	}
}

// void	draw_points(t_fdf *env)
// {
// 	img_pix_put(env, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0xFF0000);
// }

int	draw(t_fdf *env)
{
	env->data_addr = NULL;
	env->data_addr = mlx_get_data_addr(env->img, &env->bpp, &env->size_line, 
					&env->type);
	draw_points(env);
	// render(env);
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
