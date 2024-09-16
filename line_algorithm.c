/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:47:58 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/16 12:17:31 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	slope_less_than_one(t_fdf *env, t_point a, t_point b)
{
	int	p;
	int	i;
	int	dy;
	int	dx;

	dx = b.x - a.x;
	dy = b.y - a.y;
	i = -1;
	p = 2 * abs(dy) - abs(dx);
	img_pix_put(env, a.x, a.y, a.colour);
	while (++i < abs(dx))
	{
		if (dx > 0)
			a.x += 1;
		else
			a.x -= 1;
		if (p < 0)
			p = p + 2 * abs(dy);
		else
		{
			if (dy > 0)
				a.y += 1;
			else
				a.y -= 1;
			p = p + 2 * abs(dy) - 2 * abs(dx);
		}
		img_pix_put(env, a.x, a.y, a.colour);
	}
}

void	slope_bigger_than_one(t_fdf *env, t_point a, t_point b)
{
	int	p;
	int	i;
	int	dy;
	int	dx;

	dx = b.x - a.x;
	dy = b.y - a.y;
	i = -1;
	p = 2 * abs(dy) - abs(dx);
	img_pix_put(env, a.x, a.y, a.colour);
	while (++i < abs(dy))
	{
		if (dy > 0)
			a.y += 1;
		else
			a.y -= 1;
		if (p < 0)
			p = p + 2 * abs(dx);
		else
		{
			if (dx > 0)
				a.x += 1;
			else
				a.x -= 1;
			p = p + 2 * abs(dx) - 2 * abs(dy);
		}
		img_pix_put(env, a.x, a.y, a.colour);
	}
	return ;
}