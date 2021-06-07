#include "fdf.h"

static void	put_pixel(t_frame *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned  int*)dst = color;
}

void	draw_line(t_frame *image, float x1, float y1, float x2, float y2, maps *map)
{
	float a;
	float b;
	float max;
//	int color = map->z[(int)y2][(int)x2].color;

//	a = (y2 - y1) * (float)map->scale;
//	b = (x2 - x1) * (float)map->scale;
//	x1 *= (float)map->scale;
//	y1 *= (float)map->scale;
//	if (a * (float)(1 - (2 * (a < 0))) > b * (float)(1 - (2 * (b < 0))))
//		max = a * (float)(1 - (2 * (a < 0)));
//	else
//		max = b * (float)(1 - (2 * (b < 0)));
//	while ((int)(x1 - x2 * (float)map->scale) || (int)(y1 - y2 * (float)map->scale))
//	{
//		put_pixel(image, (int)x1, (int)y1, map->z[(int)y2][(int)x2].color); /** todo: x/y y/x? */
//		x1 += b / max;
//		y1 += a / max;
//	}
	x1 *= map->scale;
	y1 *= map->scale;
	x2 *= map->scale;
	y2 *= map->scale;

	x1 += map->move_x;
	y1 += map->move_y;
	x2 += map->move_x;
	y2 += map->move_y;

	a = (y2 - y1);
	b = (x2 - x1);
	if (a * (float)(1 - (2 * (a < 0))) > b * (float)(1 - (2 * (b < 0))))
		max = a * (float)(1 - (2 * (a < 0)));
	else
		max = b * (float)(1 - (2 * (b < 0)));
	while (((int)(x1 - x2) || (int)(y1 - y2)) && x1 < 1920 && y1 < 1080)
	{
		put_pixel(image, (int)x1, (int)y1, 16777215); /** todo: x/y y/x? */
		x1 += b / max;
		y1 += a / max;
	}
}

void	render(maps *map)
{
	int x;
	int y;
	t_frame	image;


	image.img = mlx_new_image(map->mlx, 1920, 1080);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_length, &image.endian);
	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			if (x < map->x - 1)
				draw_line(&image, (float)y, (float)x, (float)y, (float)x + 1, map);
			if (y < map->y - 1)
				draw_line(&image, (float)y, (float)x, (float)y + 1, (float)x, map);
		}
	}
	mlx_put_image_to_window(map->mlx, map->win, image.img, 0, 0);
}
