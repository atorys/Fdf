#include <stdlib.h>
#include <stdio.h>
#include "fractol.h"
#include <unistd.h>

typedef struct you
{
	void *mlx;
	void *win;
	int x;
	int y;
	int speed;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}				sexy;

int	my(sexy back)
{
	exit(0);
	return (0);
}

int rgb(int r, int g, int b, int a)
{
	return (r << 16 | g << 8 | b | a << 24);
}

void make(sexy boy)
{
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			mlx_pixel_put(boy.mlx, boy.win, i+boy.x, j+boy.y, rgb(boy.r, boy.g, boy.b, boy.a));
}

int key_event(int key, sexy *boy)
{
	if (key == 86)
		boy->r += 1;
	if (key == 89)
		boy->r -= 1;
	if (key == 87)
		boy->g += 1;
	if (key == 91)
		boy->g -= 1;
	if (key == 88)
		boy->b += 1;
	if (key == 92)
		boy->b -= 1;
	if (key == 123)
		boy->x -= boy->speed;
	if (key == 124)
		boy->x += boy->speed;
	if (key == 125)
		boy->y += boy->speed;
	if (key == 126)
		boy->y -= boy->speed;
	if (key == 78)
		boy->speed -= 10;
	if (key == 69)
		boy->speed += 10;
	if (key == 49)
		mlx_clear_window(boy->mlx, boy->win);
	if (key == 53)
		my(*boy);
//	mlx_string_put(boy->mlx, boy->win, 0, 0, , )
//	write(1, "\r", 1);
	printf("{rgb(%d,%d,%d) key : %d}\n", boy->r, boy->g, boy->b,key);
	make(*boy);

	return (0);
}

int main()
{
	sexy	boy;


	boy.x = 0;
	boy.y = 0;
	boy.r = 255;
	boy.g = 128;
	boy.b = 0;
	boy.a = 0;
	boy.speed = 1;
	boy.mlx = mlx_init();
	boy.win = mlx_new_window(boy.mlx, 1920, 1080, "New window");

	mlx_hook(boy.win, 2, 0, key_event, &boy);
	mlx_hook(boy.win, 17, 0, my, &boy);

	mlx_loop(boy.mlx);
	return 0;
}
