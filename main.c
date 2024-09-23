/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:50:27 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/23 11:13:15 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*initialize_env(char *str)
{
	t_fdf	*env;
	char	*title;

	env = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	if (!env)
		ft_putstr_fd("Unable to allocate memory for env variable.", 2);
	env->mlx = mlx_init();
	if (!env->mlx)
	{
		free(env);
		ft_putstr_fd("Unable to create display.", 2);
	}
	title = set_title(env, str);
	env->win = mlx_new_window(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, title);
	free(title);
	if (!env->win)
	{
		free_display_env(env);
		ft_putstr_fd("Unable to create window.", 2);
	}
	env->map = NULL;
	env->img = mlx_new_image(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!env->img)
		error_img_close_window(env);
	return (env);
}

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	initialize_camera(t_fdf *env)
{
	t_camera	*camera;

	camera = (t_camera *)ft_calloc(sizeof(t_camera), 1);
	if (!camera)
	{
		free_map_array_width(env, env->map->height, env->map->width);
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		free(env->map);
		free(env);
		ft_putstr_fd("Error initializing camera", 2);
	}
	camera->zoom = min(WINDOW_WIDTH / env->map->width / 2,
			WINDOW_HEIGHT / env->map->height / 2);
	camera->x_angle = -0.615472907;
	camera->y_angle = -0.523599;
	camera->z_angle = 0.615472907;
	camera->z_height = 1;
	camera->x_offset = 0;
	camera->y_offset = 0;
	camera->iso = 1;
	env->camera = camera;
}

int	main(int argc, char **argv)
{
	t_fdf	*env;

	if (argc == 2)
	{
		env = initialize_env(argv[1]);
		initialize_map(env, argv[1]);
		initialize_camera(env);
		set_hooks(env);
		draw(env);
		mlx_loop(env->mlx);
	}
	else
		ft_putstr_fd("Correct Usage: ./fdf <file_name>", 2);
	return (0);
}
