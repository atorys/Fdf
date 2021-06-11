#include "fdf.h"

void	put_pixel(t_frame *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void	treat_values(t_line *line, t_maps *map)
{
	float	z1;
	float	z2;

	z1 = map->z[(int)line->y1][(int)line->x1].depth;
	z2 = map->z[(int)line->y2][(int)line->x2].depth;
	line->x1 *= (float)map->scale;
	line->y1 *= (float)map->scale;
	line->x2 *= (float)map->scale;
	line->y2 *= (float)map->scale;
	z1 *= (float)map->scale / 2;
	z2 *= (float)map->scale / 2;
	line->x1 = (line->x1 - line->y1) * (float)cos(map->cos);
	line->y1 = (line->x1 + line->y1) * (float)sin(map->sin) - z1 * map->height;
	line->x2 = (line->x2 - line->y2) * (float)cos(map->cos);
	line->y2 = (line->x2 + line->y2) * (float)sin(map->sin) - z2 * map->height;
	line->x1 += (float)map->move_x;
	line->y1 += (float)map->move_y;
	line->x2 += (float)map->move_x;
	line->y2 += (float)map->move_y;
}

float	ft_max(float a, float b)
{
	if (a * (float)(1 - (2 * (a < 0))) > b * (float)(1 - (2 * (b < 0))))
		return (a * (float)(1 - (2 * (a < 0))));
	else
		return (b *(float)(1 - (2 * (b < 0))));
}
