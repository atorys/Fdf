#include "../fdf.h"
#include <fcntl.h>

static void writing_dots(void *map_fdf, maps *map)
{
	char 	*line;
	int 	fd;
	int		x;
	int 	y;

	fd = open(map_fdf, O_RDONLY);
	x = -1;
	y = -1;
	while (++y < map->y && get_next_line(fd, &line))
	{
		while (++x < map->x)
		{
			map->z[y][x].depth = ft_split(line, ' ')[0][x];
		}
		free(line);
	}
}

void	parse_me(void *map_fdf, maps *map)
{
	int		fd;
	int 	i;
	char 	*line;

	fd = open(map_fdf, O_RDONLY);
	i = 0;
	map->y = 0;
	map->x = 0;
	while (get_next_line(fd, &line))
	{
		map->y++;
		map->x = ;
		free(line);
	}
	close(fd);
	map->z = (dot **)malloc(sizeof(dot *) * (map->y + 1));
	fd = open(map_fdf, O_RDONLY);
	while (i < map->y && get_next_line(fd, &line))
	{
		map->z[i++] = (dot *)malloc(sizeof(dot) * (map->x + 1));
		free(line);
	}
	writing_dots(map_fdf, map);
}
