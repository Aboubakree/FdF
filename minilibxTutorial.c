#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


# define ESC 53   // key escape
# define ENTER 36 // key "enter"
# define FOLLOW 3 // key "f"
# define COLOR 8  // key "c"
# define UP 126   // key "arrow up"
# define DOWN 125 // key "arrow down"
# define PENGUIN 35 // key "p"
# define RAND_COLOR 15 // key "r"


int size = 10;
int follow = 0;
int color = 0x00FF00;

typedef struct s_wind
{
    void    *mlx;
    void    *window;
    int     win_height;
    int     win_width;
}           t_wind;

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
}               t_img;

typedef struct s_square
{
    int     x;
    int     y;
    int     size;
    int     color;
}               t_square;


t_img new_img(t_wind win, int img_width, int img_height)
{
    t_img img ;
    img.win = win;
    img.img_ptr = mlx_new_image(win.mlx, img_width, img_height);
    img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
    img.h = img_height;
    img.w = img_width;
    return (img);

}

t_wind new_program(int win_width, int win_height, char *str)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init(); 
	return ((t_wind) {mlx_ptr, mlx_new_window(mlx_ptr, win_width, win_height, str), win_height, win_width});
}

void    put_pixel_img(t_img img, int x, int y, int color)
{
    char    *dst;

    if (x >= 0 && y >= 0 && x <= img.w && y <= img.h){
        dst = img.addr + (y * img.line_len) + x * (img.bpp / 8);
        *(unsigned int *)dst = color;
    }
}

int     exit_tutorial(t_wind *window)
{
	if (window)
		mlx_destroy_window (window->mlx, window->window);
	exit(EXIT_SUCCESS);
}


void    draw_square(t_square sq, t_img img)
{
    int i = 0;
    int j = 0;

    while(i < sq.size)
    {
        j = 0;
        while (j < sq.size)
        {
            put_pixel_img(img, sq.x + j, sq.y + i, sq.color);
            j ++;
        }
        i ++;
    }
    // mlx_put_image_to_window(img.win.mlx, img.win.window, img.img_ptr, 0, 0);
}

/////////////////////////////////////// Hooks ////////////////////////////////////
int get_color()
{
        return (rand() % 2147483647);
}

int     read_keys(int key_pressed, void *param)
{
        t_img *img;

        img = (t_img *)param;
        if (key_pressed == ESC || !img)
                exit_tutorial(&img->win);
        else if (key_pressed == ENTER)
                draw_square((t_square){0, 0, img->w, color}, *img);
        else if (key_pressed == FOLLOW)
                follow = !follow;
        else if (key_pressed == COLOR)
                color = get_color();
        //else if (key_pressed == PENGUIN)
        //        penguin(*img);
        else
                return (-1);
        mlx_put_image_to_window(img->win.mlx, img->win.window, img->img_ptr, 0, 0);
        return (0);
}


int read_mouse(int button, int mouse_x, int mouse_y, void *param)
{
	int 		x;
	int 		y;
	t_img 		*img;
	t_square	s;

	img = (t_img *) param;
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

//////////////////////////////////////////////////////////////////////////////////


int main()
{
    t_wind  wind;
    t_img   img;

    wind = new_program(300, 300, "Hello World!");
    if (!wind.mlx || !wind.window)
        return (1);

    img  = new_img(wind, 300, 300);

    // while (i < 100)
    // {
    //     put_pixel_img(img, 150 + i, 150 + i, 0xFFFFFF);
    //     i ++;
    // }
    // // memcpy(img.addr, "s4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vf", 16*4);
    // draw_square((t_square){0, 0, 300, 0x00FF00}, img);
    // mlx_put_image_to_window (img.win.mlx, img.win.window , img.img_ptr, 0, 0);

    //+-+-+-+-+-+-+-+-+-+-+-+-+- HOOOOK +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

    mlx_key_hook (img.win.window, read_keys, &img);
    mlx_mouse_hook(img.win.window, read_mouse, &img);
    
    //+-+-+-+-+-+-+-+-+-+-+-+-+- HOOOOK +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

    mlx_hook(wind.window, 17, 0, exit_tutorial, &wind);
    mlx_loop(wind.mlx);

    return (0);
}
