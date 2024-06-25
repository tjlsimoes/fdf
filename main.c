// Getting started with minilibx

// #include "mlx.h"
// #include "mlx_int.h"
// #include <stdlib.h>

// # define WINDOW_WIDTH 600
// # define WINDOW_HEIGHT 300

// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;

// 	mlx_ptr = mlx_init();
// 	if (!mlx_ptr)
// 		return (1);
// 	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
// 	if (!win_ptr)
// 	{
// 		free(mlx_ptr);	// Guide is incorrect in this step, right?
// 		return (1);
// 	}
// 	mlx_destroy_window(mlx_ptr, win_ptr);
// 	mlx_destroy_display(mlx_ptr);
// 	free(mlx_ptr);
// }

///////////////////////////////////////////////////////////////////////////////
// Pixel drawing with the minilibx

// Computer screen: 2D object that has x and y coordinates.
// Top left corner: (0, 0).

// 1920x1080 means:
//	1080 rows of pixels on the screen.
//	each row has 1920 pixels

//	x - column number; y - row number

// Line with endpoints P1(0, 100) and P2(1920, 100)



// Encoding a color, according to the True Color standard

// Set the bits of the integer directly
//	- needed when color is somehow provided by the user
//	  or from any external source:

// int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
// {
//     return (red << 16 | green << 8 | blue);
// }

#include "./mlx.h"
#include "./mlx_int.h"
#include <stdlib.h>
#include <stdio.h>

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300

# define RED_PIXEL 0xFF0000

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_data;

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	render(t_data *data)
{
	// If window has been destroyed, we don't want to put the pixel!
	if (data->win_ptr)
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, WINDOW_HEIGHT / 2, WINDOW_WIDTH /2, RED_PIXEL);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My Window");
	if (!data.win_ptr)
	{
		free(data.mlx_ptr);		// Guide is again incorrect here, right?
		return (1);
	}
	// Setup hooks
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	// Loop will be exited if there's no window left and execute following code
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}

