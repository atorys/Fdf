#ifndef FDF_H
#define FDF_H

# include "mlx/mlx.h"

typedef struct	depth_and_color
{
	float			depth;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}				dot;

typedef struct	s_map_reading_parsing
{
	void *mlx;
	void *win;

	int	ox;
	int	oy;
	dot	**z;
}				map;

void	parse_me(void *map_fdf, map *map);


#endif
