#ifndef FDF_H
# define FDF_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include "maparse/get_next_line.h"
# include <fcntl.h>
# include <math.h>

typedef struct s_line
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;
	int		color;
}				t_line;

typedef struct s_depthandcolor
{
	float	depth;
	int		color;
}				t_dot;

typedef struct s_frame
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		end;
}				t_frame;

typedef struct s_map_reading_parsing
{
	void	*mlx;
	void	*win;

	int		x;
	int		y;
	t_dot	**z;

	int		move_x;
	int		move_y;
	int		scale;
	float	height;
	double	cos;
	double	sin;
}				t_maps;

void	error_case(void);

void	parse_me(char *map_fdf, t_maps *map);
char	**ft_split(char const *s, char c);
int		ft_strcount(char const *s, char c);

void	render(t_maps *map);
void	put_pixel(t_frame *image, int x, int y, int color);
void	treat_values(t_line *line, t_maps *map);
float	ft_max(float a, float b);

#endif
