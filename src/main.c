#include "miniRT.h"

int main(void)
{
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
	return (1);
	win_ptr = mlx_new_window(mlx_ptr, 600, 400, "test");
	if (!win_ptr)
	return (1);
	
	mlx_loop(mlx_ptr);
	return (0);
}
