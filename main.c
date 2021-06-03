#include <stdio.h>
#include "fdf.h"

int main(int argc, char *argv[])
{
	maps	map;
	char	*map_fdf;

	if (argc > 2 || argc == 1)
		return (-1);
	map_fdf = argv[1];
	parse_me(map_fdf, &map);
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, 1920, 1640, "FDF");
	return (1);
}