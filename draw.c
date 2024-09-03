/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:17:21 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/03 16:21:37 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/// NEED TO UNDERSTAND THIS FUNCTION!
void	img_pix_put(t_img *img, int x, int y, int colour)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	while (i >= 0)
	{
		// big endian: most significant bit is the leftmost bit
		if (img->type != 0)
			*pixel++ = (colour >> i ) & 0xFF;
		// little endian> least significant bit is the lefmost bit
		else
			*pixel++ = (colour >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}


// void	draw_points(t_fdf *env)
// {
// 	int	i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (i < env->map->width)
// 	{
// 		j = 0;
// 		while (j < env->map->width)
// 		{
// 			img_pix_put(env->img, i, j, 0);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	draw_points(t_fdf *env)
{
	img_pix_put(env->img, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0xFF0000);
}

void	draw(t_fdf *env)
{
	mlx_get_data_addr(env->img, &env->img->bpp, &env->img->size_line, 
					&env->img->type);
	draw_points(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

int	render(t_fdf *env)
{
	if (env->win)
		mlx_pixel_put(env->mlx, env->win, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, RED_PIXEL);
	return (0);
}
