/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:06:31 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/08/07 13:00:58 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_close_window(t_fdf *env, char *error_msg, int sys_error)
{
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	mlx_destroy_image(env->mlx, env->img);
	// img_free(env->img);
	free(env->mlx);
	free(env->map);
	free(env);
	ft_error(error_msg, sys_error);
}

void	ft_error(char *error_msg, int sys_error)
{
	if (!sys_error)
	{
		ft_printf(error_msg); // Possible need to send this to error fd.
	}
	else
		perror(error_msg);
	exit(1);
}
