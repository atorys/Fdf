#include "fdf.h"

static void	put_pixel(t_frame *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned  int*)dst = color;
}

void	treat_values(float *x1, float *y1, float *x2, float *y2, maps *map)
{
	float z1;
	float z2;

	z1 = map->z[(int)*y1][(int)*x1].depth;
	z2 = map->z[(int)*y2][(int)*x2].depth;

	*x1 *= (float)map->scale;
	*y1 *= (float)map->scale;
	*x2 *= (float)map->scale;
	*y2 *= (float)map->scale;
	z1 *= (float)map->scale / 2;
	z2 *= (float)map->scale / 2;

	*x1 = (*x1 - *y1) * cos(map->cos);
	*y1 = (*x1 + *y1) * sin(map->sin) - z1;
	*x2 = (*x2 - *y2) * cos(map->cos);
	*y2 = (*x2 + *y2) * sin(map->sin) - z2;

	*x1 += (float)map->move_x;
	*y1 += (float)map->move_y;
	*x2 += (float)map->move_x;
	*y2 += (float)map->move_y;
}



void	draw_line(t_frame *image, float x1, float y1, float x2, float y2, maps *map)
{
	float a;
	float b;
	float max;
	int color = 16777215;

	if (map->z[(int)y1][(int)x1].color != color)
		color = map->z[(int)y1][(int)x1].color;
	else if (map->z[(int)y2][(int)x2].color != color)
		color = map->z[(int)y2][(int)x2].color;

	treat_values(&x1, &y1, &x2, &y2, map);

	a = (y2 - y1);
	b = (x2 - x1);

	if (a * (float)(1 - (2 * (a < 0))) > b * (float)(1 - (2 * (b < 0))))
		max = a * (1 - (2 * (a < 0)));
	else
		max = b * (1 - (2 * (b < 0)));

	if (map->scale > 0 && (x1 < 0 || y1 < 0))
	{
		while (((int)(x1 - x2) || (int)(y1 - y2)) && x2 < 1920 && x2 >= 0 && y2 >= 0 && y2 < 1080)
		{
			put_pixel(image, (int) x2, (int) y2, color);
			x2 -= b / max;
			y2 -= a / max;
		}
	}
	else if (map->scale > 0 && (x1 >= 0 || y1 >= 0))
	{
		while (((int) (x1 - x2) || (int) (y1 - y2)) && x1 < 1920 && x1 >= 0 && y1 >= 0 && y1 < 1080)
		{
			put_pixel(image, (int) x1, (int) y1, color);
			x1 += b / max;
			y1 += a / max;
		}
	}
}

void	render(maps *map)
{
	int x;
	int y;
	t_frame	image;

	image.img = mlx_new_image(map->mlx, 1920, 1080);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_length, &image.endian);
	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (x < map->x - 1)
				draw_line(&image, (float)x, (float)y, (float)x + 1, (float)y, map);
			if (y < map->y - 1)
				draw_line(&image, (float)x, (float)y, (float)x, (float)y + 1, map);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->mlx, map->win, image.img, 0, 0);
}
