/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:50:27 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/17 10:14:55 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*initialize_env(char *str)
{
	t_fdf	*env;
	char	*title;

	env = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	if (!env)
		ft_error("Unable to allocate memory for env variable.", 1);
	env->mlx = mlx_init();
	if (!env->mlx)
	{
		free(env);
		ft_error("Unable to create display.", 1);
	}
	title = set_title(env, str);
	env->win = mlx_new_window(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, title);
	free(title);
	if (!env->win)
	{
		free_display_env(env);
		ft_error("Unable to create window.", 1);
	}
	env->map = NULL;
	env->img = mlx_new_image(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!env->img)
		error_img_close_window(env, "Unable to create image.", 1);
	return (env);
}

// Addition

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static void	initialize_camera(t_fdf *env)
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
		ft_error("Error initializing camera", 1);
	}
	camera->zoom = ft_min(WINDOW_WIDTH / env->map->width / 2,
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

		print_array(env); /////////
	
		mlx_loop(env->mlx);
		// error_close_window(env, "Mem leak check", 1);
	}
	else
		ft_printf("Correct Usage: ./fdf <file_name>");
	return (0);
}
