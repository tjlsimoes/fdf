#include "./mlx.h"
#include "./mlx_int.h"
#include "X11/X.h"
#include <stdlib.h>
#include <stdio.h>

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
} t_data;

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (!data.win_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}

	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
	return (0);
}