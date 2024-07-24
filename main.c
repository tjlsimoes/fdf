/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:50:27 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/07/24 11:29:45 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *env)
{
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	free(env->map);
	free(env);
	exit(0);
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

t_fdf	*initialize_env(char *str)
{
	t_fdf	*env;
	char	*title;

	title = ft_strjoin(ft_strdup("FDF - "), str);
	if (!title)
		ft_error("Unable to allocate memory for title.", 1);
	env = (t_fdf *)malloc(sizeof(t_fdf));
	env->mlx = mlx_init();
	if (!env->mlx)
		ft_error("Unable to create display.", 1);
	env->win = mlx_new_window(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, title);
	free(title);
	if (!env->win)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		ft_error("Unable to create window.", 1);
	}
	env->map = NULL;
	return (env);
}

int	main(int argc, char **argv)
{
	t_fdf	*env;

	if (argc == 2)
	{
		env = initialize_env(argv[1]);

		set_hooks(env);
		mlx_loop(env->mlx);
	}
	else
		ft_printf("Correct Usage: ./fdf <file_name>");
	return (0);
}
