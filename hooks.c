/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:06:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/17 12:16:04 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_hooks(t_fdf *env)
{
	// mlx_loop_hook(env->mlx, handle_no_event, env);
	// mlx_loop_hook(env->mlx, draw, env);
	// mlx_loop_hook(env->mlx, draw, env);
	// mlx_hook(env->win, 4, 0, ft_mouse_down, env);
	mlx_hook(env->win, KeyPress, KeyPressMask, handle_keypress, env);
	mlx_hook(env->win, DestroyNotify, 0, close_window, env);
	mlx_mouse_hook(env->win, handle_mouse_click, env);
}
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

int	handle_keypress(int keysym, void *params)
{
	t_fdf	*env;
	env = (t_fdf *)params;

    if (keysym == XK_Escape)
       close_window(env);
	else if (keysym == XK_Left || keysym == XK_Right || keysym == XK_Down
		|| keysym == XK_Up)
		translate(keysym, env);
	else if (keysym == XK_space )
	{
		ft_printf("Space bar!/n");
		switch_projection(env);
	}
    ft_printf("Keypress: %d\n", keysym);
	draw(env);
    return (0);
}

int	handle_mouse_click(int button, int x, int y, void *params)
{
	t_fdf	*env;

	env = (t_fdf *)params;
	if (button == 4 || button == 5)
		zoom(button, env);
	else
    	printf("Mouse click: %d, %d %d\n", button, x, y);
    return (0);
}

int	handle_no_event()
{
	// Useless function needed for no event case.
	return (0);
}