#include "../../inc/miniRT.h"



int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("%s", ERR_ARGS);
		return (1);
	}
	data.mlx = NULL;
	data.win = NULL;
	data.img.ptr = NULL;
	parse_file(&data, argv[1]);
	cam_vec(&data.scene.camera);
	init_mlx(&data);
	
	load_object_textures(&data); // NEW: Load textures here!
	
	setup_hooks(&data);
	render_scene(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img.ptr, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
