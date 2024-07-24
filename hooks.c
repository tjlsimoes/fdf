/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:06:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/07/24 11:28:43 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_hooks(t_fdf *env)
{
	mlx_loop_hook(env->mlx, handle_no_event, env);
	mlx_hook(env->win, KeyPress, KeyPressMask, handle_keypress, env);
	mlx_hook(env->win, DestroyNotify, 0, close_window, env);
	mlx_mouse_hook(env->win, handle_mouse_click, env);
}

int	handle_keypress(int keysym, t_fdf *env)
{
    if (keysym == XK_Escape)
       close_window(env);

    printf("Keypress: %d\n", keysym);
    return (0);
}

int	handle_mouse_click(int button, int x, int y)
{
    printf("Mouse click: %d, %d %d\n", button, x, y);
    return (0);
}

int	handle_no_event()
{
	// Useless function needed for no event case.
	return (0);
}