/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:06:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/17 11:47:25 by tjorge-l         ###   ########.fr       */
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
void	ft_zoom(int button, t_fdf *env)
{
	if (button == 4)
		env->camera->zoom += 2;
	else if (button == 5)
		env->camera->zoom -= 2;
	if (env->camera->zoom < 1)
		env->camera->zoom = 1;
	draw(env);
}

int	handle_keypress(int keysym, t_fdf *env)
{
    if (keysym == XK_Escape)
       close_window(env);

    printf("Keypress: %d\n", keysym);
    return (0);
}

int	handle_mouse_click(int button, int x, int y, void *params)
{
	t_fdf	*env;

	env = (t_fdf *)params;
	if (button == 4 || button == 5)
		ft_zoom(button, env);
	else
    	printf("Mouse click: %d, %d %d\n", button, x, y);
    return (0);
}

int	handle_no_event()
{
	// Useless function needed for no event case.
	return (0);
}