/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:47:58 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/16 15:30:48 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	line_low(t_fdf *env, int ax, int ay, int bx, int by)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;
	int	x;
	int	y;

	dx = bx - ax;
	dy = by - bx;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}

	d = (2 * dy) - dx;
	y = ay;
	x = ax;
	while (x <= bx)
	{
		img_pix_put(env, x, y, RED_PIXEL);
		if (d > 0)
		{
			y = y + yi;
			d = d + (2 * (dy - dx));
		}
		else
			d = d + 2 * dy;
	}
}

static void	line_high(t_fdf *env, int ax, int ay, int bx, int by)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;
	int	x;
	int	y;

	dx = bx - ax;
	dy = by - bx;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}

	d = (2 * dx) - dy;
	x = ax;
	y = ay;

	while (y <= by)
	{
		img_pix_put(env, x, y, RED_PIXEL);
		if (d > 0)
		{
			x = x + xi;
			d = d + (2 * (dx - dy));
		}
		else
			d = d + 2 * dx;
	}
}


void	draw_line(t_fdf *env, t_point a, t_point b)
{
	int	dy;
	int	dx;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (abs(dx) > abs(dy))
	{
		if (a.x > b.x)
			line_low(env, b.x, b.y, a.x, a.y);
		else
			line_low(env, a.x, a.y, b.x, b.y);
	}
	else
	{
		if (a.y > b.y)
			line_high(env, b.x, b.y, a.x, a.y);
		else
			line_high(env, a.x, a.y, b.x, b.y);
	}
}

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
	p = 2 * abs(dx) - abs(dy);
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
}
