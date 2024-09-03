/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:50:27 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/03 16:02:08 by tjorge-l         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_fdf	*env;

	if (argc == 2)
	{
		env = initialize_env(argv[1]);
		initialize_map(env, argv[1]);

		set_hooks(env);
		draw(env);

		print_array(env); /////////
		// free_map_array_width(env, env->map->height, env->map->width); /////////
	
		mlx_loop(env->mlx);
		// error_close_window(env, "Mem leak check", 1);
	}
	else
		ft_printf("Correct Usage: ./fdf <file_name>");
	return (0);
}
