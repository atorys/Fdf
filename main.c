#include <stdio.h> /** todo: delete */
#include "fdf.h"

void	error_case(void)
{
	exit(-1);
}

int main(int argc, char *argv[])
//int main(void)
{
	maps	map;
	char	*map_fdf;
	int i = 0;
	int j = 0;

	if (argc > 2 || argc == 1)
		return (-1);
//	map_fdf = argv[1];
//	map_fdf = "test_maps/42.fdf";
//	parse_me(map_fdf, &map);
//	map.mlx = mlx_init();
//	map.win = mlx_new_window(map.mlx, 1920, 1640, "FDF");
	parse_me(argv[1], &map);
	i = 0;
	while (i < map.y)
	{
		j = 0;
		while (j < map.x)
		{
			printf("%3.0f,", map.z[i][j].depth);
			printf("%d", map.z[i][j].color);
			j++;
		}
		printf("\n");
		i++;
	}
//	printf("%d", atoi_base("0123456789abcdef", 16, "3b6e6618d7"));
	return (1);
}