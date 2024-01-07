#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	main(void)
{
	t_data	img;
	t_vars	vars;

	vars.mlx = mlx_init();
	// if (mlx == NULL)
	// 	return (1);
	vars.win = mlx_new_window(vars.mlx, 700, 700, "Hello world!");
	// if (mlx_win == NULL)
	// {
	// 	free(mlx);
	// 	return (1);
	// }

	img.img = mlx_new_image(vars.mlx, 600, 600);
	// if (mlx_win == NULL)
	// {
	// 	free(mlx_win);
	// 	free(mlx);
	// 	return (1);
	// }

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);

	my_mlx_pixel_put(&img, 0, 0, 0xFF0000);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 599);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 599, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 599, 599);

	mlx_hook(vars.win, 2, 1L<<0, close, &vars);

	mlx_loop(vars.mlx);
}