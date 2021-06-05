#include <stdio.h>  /** todo: delete */
#include "fdf.h"

void	error_case(void)
{
	exit(-1);
}

int	esc(maps *map)
{
	exit(0);
	return (0);
}

int key_event(int key, maps *map)
{
	if (key == 53)
		esc(map);
	return (0);
}

void put_pixel(t_frame *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned  int*)dst = color;
}

int main(int argc, char *argv[])
{
	maps	map;
	t_frame	image;
	int i;
	int j;

	if (argc > 2 || argc == 1)
		error_case();
	parse_me(argv[1], &map);
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, 1920, 1080, "FDF");

	image.img = mlx_new_image(map.mlx, 1920, 1080);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_length, &image.endian);

	i = -1;
	while (++i < map.y)
	{
		j = -1;
		while (++j < map.x)
		{
			put_pixel(&image, i, j, map.z[i][j].color);
		}
	}
	mlx_put_image_to_window(map.mlx, map.win, image.img, 0, 0);

	mlx_key_hook(map.win, key_event, &map);

	mlx_hook(map.win, 2, 0, key_event, &map);
	mlx_hook(map.win, 17, 0, esc, &map);

	mlx_loop(map.mlx);

//	i = 0;
//	while (i < map.y)
//	{
//		j = 0;
//		while (j < map.x)
//		{
//			printf("%2.0f,", map.z[i][j].depth);
//			printf("%d", map.z[i][j].color);
//			j++;
//		}
//		printf("\n");
//		i++;
//	}
//	while (1)
//		;
//	printf("%d", atoi_base("0123456789abcdef", 16, "3b6e6618d7"));
	return (1);
}