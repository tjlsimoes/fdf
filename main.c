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

// #include "./mlx.h"
// #include "./mlx_int.h"
// #include <stdlib.h>
// #include <stdio.h>

// # define WINDOW_WIDTH 600
// # define WINDOW_HEIGHT 300

// # define RED_PIXEL 0xFF0000

// typedef struct	s_data
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// } t_data;

// int	handle_keypress(int keysym, t_data *data)
// {
// 	if (keysym == XK_Escape)
// 	{
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		data->win_ptr = NULL;
// 	}
// 	return (0);
// }

// int	render(t_data *data)
// {
// 	// If window has been destroyed, we don't want to put the pixel!
// 	if (data->win_ptr)
// 		mlx_pixel_put(data->mlx_ptr, data->win_ptr, WINDOW_WIDTH / 2,  WINDOW_HEIGHT / 2, RED_PIXEL); // Guide switches width with height
// 	return (0);
// }

// int	main(void)
// {
// 	t_data	data;

// 	data.mlx_ptr = mlx_init();
// 	if (!data.mlx_ptr)
// 		return (1);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My Window");
// 	if (!data.win_ptr)
// 	{
// 		free(data.mlx_ptr);		// Guide is again incorrect here, right?
// 		return (1);
// 	}
// 	// Setup hooks
// 	mlx_loop_hook(data.mlx_ptr, &render, &data);

// 	// mlx original function seemingly not working
// 	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

// 	mlx_loop(data.mlx_ptr);

// 	// Loop will be exited if there's no window left and execute following code
// 	mlx_destroy_display(data.mlx_ptr);
// 	free(data.mlx_ptr);
// 	return (0);
// }


///////////////////////////////////////////////////////////////////////////////
// Drawing a rectangle

// #include "./mlx.h"
// #include "./mlx_int.h"
// #include <stdlib.h>
// #include <stdio.h>

// # define WINDOW_WIDTH 600
// # define WINDOW_HEIGHT 300

// # define GREEN_PIXEL 0xFF00
// # define RED_PIXEL 0xFF0000

// typedef struct	s_data
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// } t_data;

// typedef struct s_rect
// {
// 	int	x;
// 	int y;
// 	int width;
// 	int height;
// 	int color;
// } t_rect;

// // The x and y coordinates of the rectangle correspond to its
// // left corner.

// int	handle_keypress(int keysym, t_data *data)
// {
// 	if (keysym == XK_Escape)
// 	{
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		data->win_ptr = NULL;
// 	}
// 	return (0);
// }

// int	render_rect(t_data *data, t_rect rect)
// {
// 	int	i;
// 	int	j;

// 	if (!data->win_ptr)
// 		return (1);
// 	i = rect.y;
// 	while (i < rect.y + rect.height)
// 	{
// 		j = rect.x;
// 		while (j < rect.x + rect.width)
// 			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
// 		i++;
// 	}
// 	return (0);
// }


// int	render(t_data * data)
// {
// 	render_rect(data, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
// 	render_rect(data, (t_rect){0, 0, 100, 100, RED_PIXEL});
// 	return (0);
// }

// // (t_rect){} is a compund literal. Since C99, this is a way to initialize structures
// // without having to manually assign each member. Above: passing a structure by value.

// int	main(void)
// {
// 	t_data	data;

// 	data.mlx_ptr = mlx_init();
// 	if (!data.mlx_ptr)
// 		return (1);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My Window");
// 	if (!data.win_ptr)
// 	{
// 		free(data.mlx_ptr);		// Guide is again incorrect here, right?
// 		return (1);
// 	}
// 	// Setup hooks
// 	mlx_loop_hook(data.mlx_ptr, &render, &data);

// 	// mlx original function seemingly not working
// 	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

// 	mlx_loop(data.mlx_ptr);

// 	// Loop will be exited if there's no window left and execute following code
// 	mlx_destroy_display(data.mlx_ptr);
// 	free(data.mlx_ptr);
// 	return (0);
// }

///////////////////////////////////////////////////////////////////////////////
// Drawbacks of previous approach

// #include "./mlx.h"
// #include "./mlx_int.h"
// #include <stdlib.h>
// #include <stdio.h>

// # define WINDOW_WIDTH 600
// # define WINDOW_HEIGHT 300

// # define GREEN_PIXEL 0xFF00
// # define RED_PIXEL 0xFF0000
// # define WHITE_PIXEL 0x000000

// typedef struct	s_data
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// } t_data;

// typedef struct s_rect
// {
// 	int	x;
// 	int y;
// 	int width;
// 	int height;
// 	int color;
// } t_rect;

// // The x and y coordinates of the rectangle correspond to its
// // left corner.

// int	handle_keypress(int keysym, t_data *data)
// {
// 	if (keysym == XK_Escape)
// 	{
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		data->win_ptr = NULL;
// 	}
// 	return (0);
// }

// int	render_rect(t_data *data, t_rect rect)
// {
// 	int	i;
// 	int	j;

// 	if (!data->win_ptr)
// 		return (1);
// 	i = rect.y;
// 	while (i < rect.y + rect.height)
// 	{
// 		j = rect.x;
// 		while (j < rect.x + rect.width)
// 			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
// 		i++;
// 	}
// 	return (0);
// }

// void 	render_background(t_data *data, int color)
// {
// 	int	i;
// 	int	j;

// 	if (!data->win_ptr)
// 		return ;
// 	i = 0;
// 	while (i < WINDOW_HEIGHT)
// 	{
// 		j = 0;
// 		while (j < WINDOW_WIDTH)
// 			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, color);
// 		i++;
// 	}
// }

// int	render(t_data * data)
// {
// 	render_background(data, WHITE_PIXEL);
// 	render_rect(data, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
// 	render_rect(data, (t_rect){0, 0, 100, 100, RED_PIXEL});
// 	return (0);
// }

// // (t_rect){} is a compund literal. Since C99, this is a way to initialize structures
// // without having to manually assign each member. Above: passing a structure by value.


// int	main(void)
// {
// 	t_data	data;

// 	data.mlx_ptr = mlx_init();
// 	if (!data.mlx_ptr)
// 		return (1);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My Window");
// 	if (!data.win_ptr)
// 	{
// 		free(data.mlx_ptr);		// Guide is again incorrect here, right?
// 		return (1);
// 	}
// 	// Setup hooks
// 	mlx_loop_hook(data.mlx_ptr, &render, &data);

// 	// mlx original function seemingly not working
// 	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

// 	mlx_loop(data.mlx_ptr);

// 	// Loop will be exited if there's no window left and execute following code
// 	mlx_destroy_display(data.mlx_ptr);
// 	free(data.mlx_ptr);
// 	return (0);
// }

// mlx_pixel_put() basically draws the pixel on the window directly, and the person
// who's looking at the window will see the change instantly.

// What ought to happen: wait for the whole background and rectangles to be drawn
// 						 and then push that on the window.

// Everything done without delay results in a flickering effect.

///////////////////////////////////////////////////////////////////////////////
// Using minilibx images to draw on the screen

// Prefered way of drawing things on a window: use images.
// Goal: create an image and edit its pixels directly;
//		 when this is done, push the image to the window.

// Accessing one particular pixel of the image

// Example: pixel at (5, 10), 5th pixel of the 10th row.
//			Window/image 600x300.

// Image is a one dimensional array.
// Dealing with bytes, but one pixel can take more than one byte,
// due to use of standard color standard. Amount given by bpp.

// line_len value == amount of bytes taken by one row of our image.
//				  == image_width * (bpp / 8)

// First row begins at index 0.
// Second row begins at index 2400 (600 * sizeof(int)) // sizeof(int) more exactly (bpp / 8)?

// Find correct row: 2400 * (row - 1)

// Find correct column => move in the row by the given nbr of pixels

// Move 5 pixels to the right => Multiply 5 by nbr of bytes per pixel

////////////////////////////////////////////////////////// Generalized formula:

// index = line_len * y + x * (bpp / 8);

#include "./mlx.h"
#include "./mlx_int.h"
#include <stdlib.h>
#include <stdio.h>

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300

# define GREEN_PIXEL 0xFF00
# define RED_PIXEL 0xFF0000
# define WHITE_PIXEL 0x000000

typedef struct s_img_alt
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
} t_img_alt;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img_alt	img;
} t_data;

typedef struct s_rect
{
	int	x;
	int y;
	int width;
	int height;
	int color;
} t_rect;

// The x and y coordinates of the rectangle correspond to its
// left corner.

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

void	img_pix_put(t_img_alt *img, int x, int y, int color)
{
    char    *pixel;
    int		i;

    i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    while (i >= 0)
    {
        /* big endian, MSB is the leftmost bit */
        if (img->endian != 0)
            *pixel++ = (color >> i) & 0xFF;
        /* little endian, LSB is the leftmost bit */
        else
            *pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
        i -= 8;
    }
}

int	render_rect(t_img_alt *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		i++;
	}
	return (0);
}

void 	render_background(t_img_alt *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(img, j++, i, color);
		i++;
	}
}

int	render(t_data * data)
{
	if (!data->win_ptr)
		return (1);
	render_background(&data->img, WHITE_PIXEL);
	render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

// (t_rect){} is a compund literal. Since C99, this is a way to initialize structures
// without having to manually assign each member. Above: passing a structure by value.

// void	img_pix_put(t_img_alt *img, int x, int y, int color)
// {
// 	char	*pixel;

// 	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
// 	*(int *)pixel = color;
// }

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

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	// Setup hooks
	mlx_loop_hook(data.mlx_ptr, &render, &data);

	// mlx original function seemingly not working
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	// Loop will be exited if there's no window left and execute following code
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}