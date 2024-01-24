#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ESC 53        // key escape
#define ENTER 36      // key "enter"
#define FOLLOW 3      // key "f"
#define COLOR 8       // key "c"
#define UP 126        // key "arrow up"
#define DOWN 125      // key "arrow down"
#define PENGUIN 35    // key "p"
#define RAND_COLOR 15 // key "r"
#define YELLOW 0xF0CA0C
#define ORANGE 0xED840C

int			size = 10;
int			follow = 0;
int			color = 0x00FF00;

typedef struct s_wind
{
	void	*mlx;
	void	*window;
	int		win_height;
	int		win_width;
}			t_wind;

typedef struct s_img
{
	t_wind	win;
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

typedef struct s_square
{
	int		x;
	int		y;
	int		size;
	int		color;
}			t_square;

t_img	new_img(t_wind win, int img_width, int img_height)
{
	t_img	img;

	img.win = win;
	img.img_ptr = mlx_new_image(win.mlx, img_width, img_height);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len,
			&img.endian);
	img.h = img_height;
	img.w = img_width;
	return (img);
}

t_wind	new_program(int win_width, int win_height, char *str)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	return ((t_wind){mlx_ptr, mlx_new_window(mlx_ptr, win_width, win_height,
			str), win_height, win_width});
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x <= img.w && y <= img.h)
	{
		dst = img.addr + (y * img.line_len) + x * (img.bpp / 8);
		*(unsigned int *)dst = color;
	}
}

int	exit_tutorial(t_wind *window)
{
	if (window)
		mlx_destroy_window(window->mlx, window->window);
	exit(EXIT_SUCCESS);
}

void	draw_square(t_square sq, t_img img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < sq.size)
	{
		j = 0;
		while (j < sq.size)
		{
			put_pixel_img(img, sq.x + j, sq.y + i, sq.color);
			j++;
		}
		i++;
	}
	// mlx_put_image_to_window(img.win.mlx, img.win.window, img.img_ptr, 0, 0);
}

void		penguin(t_img img);

/////////////////////////////////////// Hooks function
////////////////////////////////////
int	get_color(void)
{
	return (rand() % 2147483647);
}

int	read_keys(int key_pressed, void *param)
{
	t_img	*img;

	img = (t_img *)param;
	if (key_pressed == ESC || !img)
		exit_tutorial(&img->win);
	else if (key_pressed == ENTER)
		draw_square((t_square){0, 0, img->w, color}, *img);
	else if (key_pressed == FOLLOW)
		follow = !follow;
	else if (key_pressed == COLOR)
		color = get_color();
	else if (key_pressed == PENGUIN)
		penguin(*img);
	else
		return (-1);
	mlx_put_image_to_window(img->win.mlx, img->win.window, img->img_ptr, 0, 0);
	return (0);
}

int	read_mouse(int button, int mouse_x, int mouse_y, void *param)
{
	int			x;
	int			y;
	t_img		*img;
	t_square	s;

	img = (t_img *)param;
	if (!img)
		return (-1);
	if (mouse_x < 0 || mouse_y < 0 || mouse_x > img->w || mouse_y > img->h)
		return (2);
	x = ((mouse_x % img->w) / size) * size;
	y = ((mouse_y % img->h) / size) * size;
	s = (t_square){x, y, size, color};
	draw_square(s, *img);
	mlx_put_image_to_window(img->win.mlx, img->win.window, img->img_ptr, 0, 0);
	(void)button;
	return (0);
}

int	continuous_read_keys(int key_pressed, void *param)
{
	t_img	*img;

	img = (t_img *)param;
	if (!img)
		exit_tutorial(&img->win);
	else if (key_pressed == UP)
	{
		if (size < img->w / 4)
			size++;
	}
	else if (key_pressed == DOWN)
	{
		if (size > 1)
			size--;
	}
	else if (key_pressed == RAND_COLOR)
		color = get_color();
	return (0);
}

int	follow_mouse(int mouse_x, int mouse_y, void *param)
{
	int			x;
	int			y;
	t_img		*img;
	t_square	s;

	img = (t_img *)param;
	if (!img)
		return (1);
	if (mouse_x < 0 || mouse_y < 0 || mouse_x > img->w || mouse_y > img->h)
		return (2);
	if (!follow)
		return (3);
	x = ((mouse_x % img->w) / size) * size;
	y = ((mouse_y % img->h) / size) * size;
	s = (t_square){x, y, size, color};
	draw_square(s, *img);
	mlx_put_image_to_window(img->win.mlx, img->win.window, img->img_ptr, 0, 0);
	return (0);
}

//////////////////////////////////////////////////////////////////////////////////

int	main(void)
{
	t_wind	wind;
	t_img	img;

	wind = new_program(300, 300, "Hello World!");
	if (!wind.mlx || !wind.window)
		return (1);
	img = new_img(wind, 300, 300);
	// while (i < 100)
	// {
	//     put_pixel_img(img, 150 + i, 150 + i, 0xFFFFFF);
	//     i ++;
	// }
	// // memcpy(img.addr,
		"s4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vf",
		16*4);
		// draw_square((t_square){0, 0, 300, 0x00FF00}, img);
		// mlx_put_image_to_window (img.win.mlx, img.win.window , img.img_ptr,
			0,
		0);
		//+-+-+-+-+-+-+-+-+-+-+-+-+- HOOOOK +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
		mlx_key_hook(img.win.window, read_keys, &img);
		mlx_mouse_hook(img.win.window, read_mouse, &img);
		mlx_hook(img.win.window, 2, 0, continuous_read_keys, &img);
		mlx_hook(img.win.window, 6, 0, follow_mouse, &img);
		//+-+-+-+-+-+-+-+-+-+-+-+-+- HOOOOK +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
		mlx_hook(img.win.window, 17, 0, exit_tutorial, &img);
		mlx_loop(img.win.mlx);
		return (0);
}

void	penguin(t_img img)
{
	t_square s1;
	for (int row1 = 160; row1 <= 240; row1 += 10)
	{
		s1 = (t_square){row1, 100, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row2 = 150; row2 <= 250; row2 += 10)
	{
		s1 = (t_square){row2, 110, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row3 = 140; row3 <= 160; row3 += 10)
	{
		s1 = (t_square){row3, 120, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row3 = 170; row3 <= 230; row3 += 10)
	{
		s1 = (t_square){row3, 120, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	for (int row3 = 240; row3 <= 260; row3 += 10)
	{
		s1 = (t_square){row3, 120, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row4 = 140; row4 <= 150; row4 += 10)
	{
		s1 = (t_square){row4, 130, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row4 = 160; row4 <= 240; row4 += 10)
	{
		s1 = (t_square){row4, 130, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	for (int row4 = 250; row4 <= 260; row4 += 10)
	{
		s1 = (t_square){row4, 130, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row5 = 140; row5 <= 260; row5 += 10)
	{
		s1 = (t_square){row5, 140, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	{
		s1 = (t_square){140, 140, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){170, 140, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){180, 140, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){220, 140, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){230, 140, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){260, 140, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row6 = 140; row6 <= 260; row6 += 10)
	{
		s1 = (t_square){row6, 150, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	{
		s1 = (t_square){140, 150, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){160, 150, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){170, 150, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){190, 150, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){210, 150, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){220, 150, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){240, 150, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){260, 150, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row7 = 140; row7 <= 260; row7 += 10)
	{
		s1 = (t_square){row7, 160, 10, 0x000000};
		draw_square(s1, img);
	}
	{
		s1 = (t_square){150, 160, 10, 0xFFFFFF};
		draw_square(s1, img);
		s1 = (t_square){200, 160, 10, 0xFFFFFF};
		draw_square(s1, img);
		s1 = (t_square){250, 160, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	for (int row8 = 140; row8 <= 260; row8 += 10)
	{
		s1 = (t_square){row8, 170, 10, 0x000000};
		draw_square(s1, img);
	}
	{
		s1 = (t_square){150, 170, 10, 0xFFFFFF};
		draw_square(s1, img);
		s1 = (t_square){160, 170, 10, 0xFFFFFF};
		draw_square(s1, img);
		s1 = (t_square){190, 170, 10, 0xFFFFFF};
		draw_square(s1, img);
		s1 = (t_square){200, 170, 10, 0xffff00}; /*YELLOW*/
		draw_square(s1, img);
		s1 = (t_square){210, 170, 10, 0xFFFFFF};
		draw_square(s1, img);
		s1 = (t_square){240, 170, 10, 0xFFFFFF};
		draw_square(s1, img);
		s1 = (t_square){250, 170, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	for (int row9 = 140; row9 <= 260; row9 += 10)
	{
		s1 = (t_square){row9, 180, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	{
		s1 = (t_square){140, 180, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){260, 180, 10, 0x000000};
		draw_square(s1, img);
		s1 = (t_square){190, 180, 10, 0xffff00};
		draw_square(s1, img);
		s1 = (t_square){200, 180, 10, YELLOW};
		draw_square(s1, img);
		s1 = (t_square){210, 180, 10, YELLOW};
		draw_square(s1, img);
	}
	for (int row10 = 130; row10 <= 270; row10 += 10)
	{
		s1 = (t_square){row10, 190, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row10 = 160; row10 <= 240; row10 += 10)
	{
		s1 = (t_square){row10, 190, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	for (int row10 = 180; row10 <= 220; row10 += 10)
	{
		s1 = (t_square){row10, 190, 10, YELLOW};
		draw_square(s1, img);
	}
	for (int row11 = 120; row11 <= 280; row11 += 10)
	{
		s1 = (t_square){row11, 200, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row11 = 160; row11 <= 240; row11 += 10)
	{
		s1 = (t_square){row11, 200, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	for (int row11 = 190; row11 <= 210; row11 += 10)
	{
		s1 = (t_square){row11, 200, 10, YELLOW};
		draw_square(s1, img);
	}
	for (int row12 = 110; row12 <= 280; row12 += 10)
	{
		s1 = (t_square){row12, 210, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row12 = 160; row12 <= 240; row12 += 10)
	{
		s1 = (t_square){row12, 210, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	for (int row13 = 100; row13 <= 290; row13 += 10)
	{
		s1 = (t_square){row13, 220, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row13 = 160; row13 <= 240; row13 += 10)
	{
		s1 = (t_square){row13, 220, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	{
		s1 = (t_square){140, 220, 10, 0xFFFFFF};
		draw_square(s1, img);
		s1 = (t_square){260, 220, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	for (int row14 = 100; row14 <= 290; row14 += 10)
	{
		s1 = (t_square){row14, 230, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row14 = 160; row14 <= 240; row14 += 10)
	{
		s1 = (t_square){row14, 230, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	{
		s1 = (t_square){130, 230, 10, 0xFFFFFF};
		draw_square(s1, img);
		s1 = (t_square){140, 230, 10, 0xFFFFFF};
		draw_square(s1, img);
		s1 = (t_square){260, 230, 10, 0xFFFFFF};
		draw_square(s1, img);
		s1 = (t_square){270, 230, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	for (int row15 = 150; row15 <= 250; row15 += 10)
	{
		s1 = (t_square){row15, 240, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row15 = 160; row15 <= 240; row15 += 10)
	{
		s1 = (t_square){row15, 240, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	for (int row16 = 150; row16 <= 250; row16 += 10)
	{
		s1 = (t_square){row16, 250, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row16 = 170; row16 <= 230; row16 += 10)
	{
		s1 = (t_square){row16, 250, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
	for (int row17 = 160; row17 <= 240; row17 += 10)
	{
		s1 = (t_square){row17, 260, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row18 = 160; row18 <= 240; row18 += 10)
	{
		s1 = (t_square){row18, 270, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row18 = 170; row18 <= 230; row18 += 10)
	{
		s1 = (t_square){row18, 270, 10, ORANGE};
		draw_square(s1, img);
	}
	{
		s1 = (t_square){200, 270, 10, 0x000000};
		draw_square(s1, img);
	}
	for (int row19 = 160; row19 <= 240; row19 += 10)
	{
		s1 = (t_square){row19, 280, 10, 0x000000};
		draw_square(s1, img);
	}
	{
		s1 = (t_square){200, 280, 10, 0xFFFFFF};
		draw_square(s1, img);
	}
}