#include "fdf.h"

static void	drawing(t_frame *image, t_line line, float a, float b)
{
	float	max;

	max = ft_max(a, b);
	if (line.x1 < 0 || line.y1 < 0)
	{
		while (((int)(line.x1 - line.x2) || (int)(line.y1 - line.y2)) && line.x2 < 1920 && \
				line.x2 >= 0 && line.y2 >= 0 && line.y2 < 1080)
		{
			put_pixel(image, (int)line.x2, (int)line.y2, line.color);
			line.x2 -= b / max;
			line.y2 -= a / max;
		}
	}
	else if (line.x1 >= 0 || line.y1 >= 0)
	{
		while (((int)(line.x1 - line.x2) || (int)(line.y1 - line.y2)) && line.x1 < 1920 && \
				line.x1 >= 0 && line.y1 >= 0 && line.y1 < 1080)
		{
			put_pixel(image, (int)line.x1, (int)line.y1, line.color);
			line.x1 += b / max;
			line.y1 += a / max;
		}
	}
}

static void	draw_line(t_frame *image, t_line line, t_maps *map)
{
	float	a;
	float	b;

	if (map->z[(int)line.y1][(int)line.x1].color != line.color)
		line.color = map->z[(int)line.y1][(int)line.x1].color;
	else if (map->z[(int)line.y2][(int)line.x2].color != line.color)
		line.color = map->z[(int)line.y2][(int)line.x2].color;
	treat_values(&line, map);
	a = (line.y2 - line.y1);
	b = (line.x2 - line.x1);
	if (map->scale > 0)
		drawing(image, line, a, b);
}

static void	process_dot(t_frame img, int x, int y, t_maps *map)
{
	t_line	line;

	line.x1 = (float)x;
	line.y1 = (float)y;
	line.color = 16777215;
	if (x < map->x - 1)
	{
		line.x2 = (float)(x + 1);
		line.y2 = (float)y;
		draw_line(&img, line, map);
	}
	if (y < map->y - 1)
	{
		line.x2 = (float)x;
		line.y2 = (float)(y + 1);
		draw_line(&img, line, map);
	}
}

void	render(t_maps *map)
{
	int		x;
	int		y;
	t_frame	img;

	img.img = mlx_new_image(map->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.length, &img.end);
	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
			process_dot(img, x, y, map);
	}
	mlx_put_image_to_window(map->mlx, map->win, img.img, 0, 0);
}
