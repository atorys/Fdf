#ifndef FDF_H
#define FDF_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include "maparse/get_next_line.h"
# include <fcntl.h>

typedef struct	depth_and_color
{
	float	depth;
	int 	color;
}				dot;

typedef struct	s_map_reading_parsing
{
	void *mlx;
	void *win;

	int	x;
	int	y;
	dot	**z;
}				maps;

void			error_case(void);
int				parse_me(char *map_fdf, maps *map);
char			**ft_split(char const *s, char c);
unsigned int	ft_strcount(char const *s, char c);
//int	atoi_base(char *base, int b, const char *str);
//int multy(int b, int n);

#endif
