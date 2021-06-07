#include "fdf.h"

static void	put_pixel(t_frame *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned  int*)dst = color;
}

static void	draw_line(t_frame *image, float x1, float y1, float x2, float y2, maps *map)
{
	float a;
	float b;
	float max;

	a = (y2 - y1) * (float)map->scale;
	b = (x2 - x1) * (float)map->scale;
	x1 *= (float)map->scale;
	y1 *= (float)map->scale;
	if (a * (float)(1 - (2 * (a < 0))) > b * (float)(1 - (2 * (b < 0))))
		max = a * (float)(1 - (2 * (a < 0)));
	else
		max = b * (float)(1 - (2 * (b < 0)));
	while ((int)(x1 - x2 * (float)map->scale) || (int)(y1 - y2 * (float)map->scale))
	{
		put_pixel(image, (int)x1, (int)y1, map->z[(int)y2][(int)x2].color); /** todo: x/y y/x? */
		x1 += b / max;
		y1 += a / max;
	}
}

void	render(t_frame *image, maps *map)
{
	int x;
	int y;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			if (x < map->x - 1)
				draw_line(image, (float)y, (float)x, (float)y, (float)x + 1, map);
			if (y < map->y - 1)
				draw_line(image, (float)y, (float)x, (float)y + 1, (float)x, map);
		}
	}
}
