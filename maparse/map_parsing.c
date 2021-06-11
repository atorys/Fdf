#include "../fdf.h"
#include <fcntl.h>

static int	multy(int b, int n)
{
	int	a;

	a = b;
	if (n == 0)
		return (1);
	while (--n > 0)
		b *= a;
	return (b);
}

static int	atoi_base(const char *base, int b, const char *str)
{
	int	result;
	int	i;
	int	n;
	int	digit;

	result = 0;
	i = -1;
	n = (int)ft_strlen(str) - 1;
	while (str[++i])
	{
		digit = 0;
		while (str[i] != base[digit] && base[digit] != '\0')
			digit++;
		result += digit * multy(b, n--);
	}
	return (result);
}

void	devide_depth_color(char *value, t_maps *map, int i, int j)
{
	char	*comma;
	char	*temp;
	char	*temp1;
	int		k;

	temp = value;
	comma = ft_strchr(value, ',');
	map->z[i][j].color = 16777215;
	if (!comma)
		map->z[i][j].depth = (float)atoi_base("0123456789", 10, value);
	else
	{
		k = 0;
		while (value[k] != ',')
			k++;
		temp1 = ft_substr(value, 0, k);
		map->z[i][j].depth = (float)atoi_base("0123456789", 10, temp1);
		free(temp1);
		comma += 3;
		temp1 = ft_strdup(comma);
		map->z[i][j].color = atoi_base("0123456789abcdef", 16, temp1);
		free(temp1);
	}
	free(temp);
}

static void	parse_values(char *map_fdf, t_maps *map)
{
	int		fd;
	int		i;
	int		j;
	char	*line;
	char	**values;

	i = -1;
	fd = open(map_fdf, O_RDONLY);
	while (++i < map->y && get_next_line(fd, &line) > 0)
	{
		map->z[i] = (t_dot *)malloc(sizeof(t_dot) * (map->x + 1));
		if (!map->z[i])
			error_case();
		values = ft_split(line, ' ');
		j = -1;
		while (values[++j])
			devide_depth_color(values[j], map, i, j);
		free(line);
		free(values);
	}
	close(fd);
}

void	parse_me(char *map_fdf, t_maps *map)
{
	int		fd;
	char	*line;

	fd = open(map_fdf, O_RDONLY);
	if (fd < 0)
		error_case();
	map->y = 0;
	map->x = 0;
	while (get_next_line(fd, &line) > 0)
	{
		map->y++;
		map->x = ft_strcount(line, ' ');
		free(line);
	}
	free(line);
	close(fd);
	map->z = (t_dot **)malloc(sizeof(t_dot *) * (map->y + 1));
	if (!map->z)
		error_case();
	parse_values(map_fdf, map);
}
