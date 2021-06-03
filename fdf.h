#ifndef FDF_H
#define FDF_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include "maparse/get_next_line.h"
# include <fcntl.h>

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

	int	x;
	int	y;
	dot	**z;
}				maps;

void	parse_me(void *map_fdf, maps *map);
char	**ft_split(char const *s, char c);

#endif
