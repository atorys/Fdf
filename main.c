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

void draw_line(t_frame *image, float x1, float y1, float x2, float y2, maps *map)
{
	float a;
	float b;
	float c;
	float x = x1;
	float y = y1;
	float max;
	int step;

	a = y2 - y1;
	b = x2 - x1;
	c = y1 * x2 - y2 *x1;
	if (a * (1 - (2 * (a < 0))) > b * (1 - (2 * (b < 0))))
		max = a * (1 - (2 * (a < 0)));
	else
		max = b * (1 - (2 * (b < 0)));
	a /= max;
	b /= max;
	while ((int)(x - x2) || (int)(y - y2))
	{
		put_pixel(image, (int)x, (int)y, 16777215);
		x += a;
		y += b;
	}
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

//	i = -1;
//	while (++i < map.y)
//	{
//		j = -1;
//		while (++j < map.x)
//		{
//			put_pixel(&image, i, j, map.z[i][j].color);
//		}
//	}
	draw_line(&image, 300, 100, 900, 300, &map);
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