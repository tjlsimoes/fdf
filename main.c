/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:50:27 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/07/23 11:56:47 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keypress(int keysym, t_fdf *env)
{
    if (keysym == XK_Escape)
        mlx_destroy_window(env->mlx, env->win);

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


int	destroy_window(t_fdf *env)
{
	mlx_destroy_window(env->mlx, env->win);
	return (0);
}

int	main(void)
{
	t_fdf	env;

	env.mlx = mlx_init();
	if (!env.mlx)
		return (1);
	env.win = mlx_new_window(env.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (!env.win)
	{
		mlx_destroy_display(env.mlx);
		free(env.mlx);
		return (1);
	}

	mlx_loop_hook(env.mlx, &handle_no_event, &env);
	mlx_hook(env.win, KeyPress, KeyPressMask, handle_keypress, &env);
	mlx_hook(env.win, DestroyNotify, 0, destroy_window, &env);
	mlx_mouse_hook(env.win, handle_mouse_click, &env);

	mlx_loop(env.mlx);

    mlx_destroy_display(env.mlx);
    free(env.mlx);
	return (0);
}