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

int key_event(int key, maps *map, t_frame *image)
{
	if (key == 53)
		esc(map);
	if (key == 124)
		map->move_x += 10;
	if (key == 123)
		map->move_x -= 10;
	if (key == 125)
		map->move_y += 10;
	if (key == 126)
		map->move_y -= 10;
	if (key == 69)
		map->scale += 10;
	if (key == 79)
		map->scale -= 10;
	if (key > 122 && key < 127 || key == 69 || key == 79)
	{
		mlx_clear_window(map->mlx, map->win);
		render(image, map);
		mlx_put_image_to_window(map->mlx, map->win, image->img, 0, 0);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	maps	map;
	t_frame	image;

	if (argc > 2 || argc == 1)
		error_case();
	parse_me(argv[1], &map);

	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, 1920, 1080, "FDF");

	image.img = mlx_new_image(map.mlx, 1920, 1080);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_length, &image.endian);

//	draw_line(&image, 300, 100, 900, 300, &map);
	render(&image, &map);
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
	return (1);
}