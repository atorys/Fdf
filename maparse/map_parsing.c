#include "../fdf.h"
#include <fcntl.h>

static int multy(int b, int n)
{
	int a;

	a = b;
	if (n == 0)
		return (1);
	while (--n > 0)
		b *= a;
	return (b);
}
static int	atoi_base(char *base, int b, const char *str)
{
	int	result;
	int	i;
	int n;
	int digit;

	result = 0;
	i = -1;
	n = ft_strlen(str) - 1;
	while (str[++i])
	{
		digit = 0;
		while (str[i] != base[digit] && base[digit] != '\0')
			digit++;
		result += digit * multy(b, n--);
	}
	return (result);
}

int	rabotaem(char *map_fdf, maps *map)
{
	int		fd;
	int 	i;
	int 	j;
	char 	*line;
	char 	**arr;
	char 	*comma;
	char 	*temp;
	int 	k;
	char 	*temp1;

	i = 0;
	fd = open(map_fdf, O_RDONLY);
	while (i < map->y && get_next_line(fd, &line) > 0)
	{
		map->z[i] = (dot *)malloc(sizeof(dot) * (map->x + 1));
		if (!map->z[i])
			error_case();
		arr = ft_split(line, ' ');
		j = 0;
		while (arr[j])
		{
			temp = arr[j];
			comma = ft_strchr(arr[j], ',');
			if (!comma)
			{
				map->z[i][j].depth = (float)atoi_base("0123456789", 10, arr[j]);
				map->z[i][j].color = 16777215;
			}
			else
			{
				k = 0;
				while (arr[j][k] != ',')
					k++;
				temp1 = ft_substr(arr[j], 0, k);
				map->z[i][j].depth = (float)atoi_base("0123456789", 10, temp1);
				free(temp1);
				comma += 3;
				temp1 = ft_strdup(comma);
				map->z[i][j].color = atoi_base("0123456789abcdef", 16, temp1);
				free(temp1);
			}
			free(temp);
			j++;
		}
		i++;
		free(line);
		free(arr);
	}
	close(fd);
	return (1);
}

int	parse_me(char *map_fdf, maps *map)
{
	int		fd;
	char 	*line;

	fd = open(map_fdf, O_RDONLY);
	map->y = 0;
	map->x = 0;
	while (get_next_line(fd, &line))
	{
		map->y++;
		map->x = (int)ft_strcount(line, ' ');
		free(line);
	}
	close(fd);
	map->z = (dot **)malloc(sizeof(dot *) * (map->y + 1));
	if (!map->z)
		error_case();
	return (rabotaem(map_fdf, map));
}
