#ifndef FDF_H
#define FDF_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include "maparse/get_next_line.h"
# include <fcntl.h>
# include <math.h>

typedef struct	depth_and_color
{
	float	depth;
	int 	color;
}				dot;

typedef struct	s_frame
{
	void	*img;
	char 	*addr;
	int 	bpp;
	int 	line_length;
	int 	endian;
}				t_frame;

typedef struct	s_map_reading_parsing
{
	void	*mlx;
	void	*win;

	int		x;
	int		y;
	dot		**z;

	int		move_x;
	int		move_y;
	int		scale;
	double	cos;
	double	sin;
}				maps;

void			error_case(void);

void			parse_me(char *map_fdf, maps *map);
char			**ft_split(char const *s, char c);
unsigned int	ft_strcount(char const *s, char c);

void			render(maps *map);
void			draw_line(t_frame *image, float x1, float y1, float x2, float y2, maps *map);

#endif
