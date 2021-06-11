#include "fdf.h"

void	error_case(void)
{
	write(2, "Error", 5);
	exit(-1);
}

static int	esc(void)
{
	exit(0);
}

static void	more_key_event(int key, t_maps *map)
{
	if (key == 69)
		map->height += (float)0.2;
	if (key == 78)
		map->height -= (float)0.2;
	if (key == 123)
		map->cos += 0.2;
	if (key == 124)
		map->cos -= 0.2;
	if (key == 126)
		map->sin += 0.2;
	if (key == 125)
		map->sin -= 0.2;
}

int	key_event(int key, t_maps *map)
{
	if (key == 53)
		esc();
	if (key == 2)
		map->move_x -= 50;
	if (key == 0)
		map->move_x += 50;
	if (key == 1)
		map->move_y -= 50;
	if (key == 13)
		map->move_y += 50;
	if (key == 24)
		map->scale += 4;
	if (key == 27)
		map->scale -= 4;
	if (key == 69 || key == 78 || (key >= 123 && key <= 126))
		more_key_event(key, map);
	mlx_clear_window(map->mlx, map->win);
	render(map);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_maps	map;

	if (argc > 2 || argc == 1)
		error_case();
	parse_me(argv[1], &map);
	map.mlx = mlx_init();
	if (!map.mlx)
		error_case();
	map.win = mlx_new_window(map.mlx, 1920, 1080, "FDF");
	map.scale = 1;
	map.height = 1;
	map.move_x = 1920 / 2;
	map.move_y = 1080 / 4;
	map.sin = 0.8;
	map.cos = 0.8;
	render(&map);
	mlx_hook(map.win, 2, 0, key_event, &map);
	mlx_hook(map.win, 17, 0, esc, &map);
	mlx_loop(map.mlx);
	return (1);
}
