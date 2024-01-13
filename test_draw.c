#include <mlx.h>
#include <stdlib.h>
#include <math.h>

// typedef struct	s_data
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// }				t_data;

// typedef struct s_point
// {
//     float     x;
//     float     y;
//     int     z;
//     int     color;
// }              t_point;

// int get_steps(t_point point1, t_point point2)
// {
// 	int dx;
// 	int dy;
//     int steps;

//     dx = point1.x > point2.x ? point1.x - point2.x : point2.x - point1.x;
// 	dy = point1.y > point2.y ? point1.y - point2.y : point2.y - point1.y;
//     steps = dx > dy ? dx : dy;
//     return (steps);
    
// }

// void draw_line(t_data *data, t_point point1, t_point point2)
// {
// 	float x_increment;
// 	float y_increment;
//     t_point result_point;
//     int     steps;

//     steps = get_steps(point1, point2);
// 	x_increment = (point2.x - point1.x) / (float)steps;
// 	y_increment = (point2.y - point1.y) / (float)steps;
//     result_point.x = point1.x;
//     result_point.y = point1.y;
//     result_point.color = point1.color;
// 	mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)result_point.x, (int)result_point.y, 0x0000FF);

// 	for (int k = 0; k < steps; k++)
// 	{
// 		result_point.x = result_point.x + x_increment;
// 		result_point.y = result_point.y + y_increment;
// 		mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)result_point.x, (int)result_point.y, 0x0000FF);
// 	}
// }

#include <stdio.h>
int	main()
{
	// t_data	data;
	// int		width = 800;
	// int		height = 600;

	// data.mlx_ptr = mlx_init();
	// data.win_ptr = mlx_new_window(data.mlx_ptr, width, height, "DDA Line Drawing");

	// int x1 = 100, y1 = 100;
	// int x2 = 150, y2 = 300;
	// t_point point1, point2;
	// point1.x = 100;
	// point1.y = 100;
	// point2.x = 300;
	// point2.y = 300;

	// drawLine1(&data, point1, point2);
	// drawLine2(&data, x1, y1, x2, y2);

	// mlx_loop(data.mlx_ptr);
	// int dx = x2 - x1;
	// int dy = y2 - y1;
	// printf("get_steps : %d\nabs() : %d", get_steps(point1, point2), (abs(dx) > abs(dy) ? abs(dx) : abs(dy)));

	float y = 0.1;
	float x = 0, i = 1;
	while (i < 20)
	{
		x = x + y;
		printf("i = %d || x = %d\n", (int)i, (int)x);
		i ++;
	}
	

	return (0);
}