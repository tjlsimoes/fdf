#include "mlx.h"
#include "mlx_int.h"

int	main(void)
{
	void	*img;
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	img = mlx_new_image(mlx, 1920, 1080);
}