/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:06:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/30 10:44:13 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_hooks(t_fdf *env)
{
	mlx_hook(env->win, KeyPress, KeyPressMask, handle_keypress, env);
	mlx_hook(env->win, DestroyNotify, 0, close_window, env);
	mlx_mouse_hook(env->win, handle_mouse_click, env);
}

int	handle_keypress(int keysym, void *params)
{
	t_fdf	*env;

	env = (t_fdf *)params;
	if (keysym == XK_Escape)
		close_window(env);
	else if (keysym == XK_Left || keysym == XK_Right || keysym == XK_Down
		|| keysym == XK_Up)
		translate(keysym, env);
	else if (keysym == XK_1 || keysym == XK_2 || keysym == XK_3
		|| keysym == XK_4 || keysym == XK_5 || keysym == XK_6)
		change_angle(keysym, env);
	else if (keysym == XK_space)
		switch_projection(env);
	else if (keysym == XK_0)
		reset(env);
	return (0);
}

int	handle_mouse_click(int button, int x, int y, void *params)
{
	t_fdf	*env;

	env = (t_fdf *)params;
	if (button == 4 || button == 5)
		zoom(button, env);
	else
		ft_printf("Not all mouse buttons enabled: button: %d, x: %d y: %d\n", button, x, y);
	return (0);
}
