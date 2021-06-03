#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"

int main(int argc, char *argv[])
{
	map		*map;
	char	*map_fdf;

	if (argc > 2 || argc == 1)
		return (-1);
	map = (map *)malloc(sizeof(map));
	map_fdf = argv[1];
	parse_me(map_fdf, map);
}