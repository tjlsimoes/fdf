/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:06:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/07/24 10:06:42 by tjorge-l         ###   ########.fr       */
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