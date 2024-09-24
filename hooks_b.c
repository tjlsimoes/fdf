/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:41:10 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/24 10:19:33 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(int button, t_fdf *env)
{
	if (button == 4)
		env->camera->zoom += 2;
	else if (button == 5)
		env->camera->zoom -= 2;
	if (env->camera->zoom < 1)
		env->camera->zoom = 1;
	draw(env);
}

void	change_angle(int keysym, t_fdf *env)
{
	if (keysym == XK_1)
		env->camera->x_angle -= 0.5;
	else if (keysym == XK_2)
		env->camera->x_angle += 0.5;
	else if (keysym == XK_3)
		env->camera->y_angle -= 0.5;
	else if (keysym == XK_4)
		env->camera->y_angle += 0.5;
	else if (keysym == XK_5)
		env->camera->z_angle -= 0.5;
	else if (keysym == XK_6)
		env->camera->z_angle += 0.5;
}

void	translate(int keycode, t_fdf *env)
{
	if (keycode == XK_Left)
		env->camera->x_offset -= 10;
	else if (keycode == XK_Right)
		env->camera->x_offset += 10;
	else if (keycode == XK_Down)
		env->camera->y_offset += 10;
	else if (keycode == XK_Up)
		env->camera->y_offset -= 10;
}

void	switch_projection(t_fdf *env)
{
	if (env->camera->iso)
	{
		env->camera->x_angle = -0.523599;
		env->camera->y_angle = -0.261799;
		env->camera->z_angle = 0;
	}
	else
	{
		env->camera->x_angle = -0.615472907;
		env->camera->y_angle = -0.523599;
		env->camera->z_angle = 0.615472907;
	}
	env->camera->iso = !env->camera->iso;
}

void	reset(t_fdf *env)
{
	env->camera->x_angle = -0.615472907;
	env->camera->y_angle = -0.523599;
	env->camera->z_angle = 0.615472907;
	env->camera->iso = !env->camera->iso;
}
