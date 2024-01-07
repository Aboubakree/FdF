#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color) {
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_data *img, int x, int y, int size, int color) {
	for (int i = x; i < x + size; i++) {
		for (int j = y; j < y + size; j++) {
            if (i == x || i == x + size - 1 || j == y || j == y + size - 1)
            {
                my_mlx_pixel_put(img, i, j, color);
            }
            
			
		}
	}
}

void	draw_circle(t_data *img, int centerX, int centerY, int radius, int color) {
	for (int i = centerX - radius; i <= centerX + radius; i++) {
		for (int j = centerY - radius; j <= centerY + radius; j++) {
			if ((i - centerX) * (i - centerX) + (j - centerY) * (j - centerY) <= radius * radius) {
				my_mlx_pixel_put(img, i, j, color);
			}
		}
	}
}

void	draw_circle_outline(t_data *img, int centerX, int centerY, int radius, int color) {
	for (int x = centerX - radius; x <= centerX + radius; x++) {
		for (int y = centerY - radius; y <= centerY + radius; y++) {
			double distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
			if (fabs(distance - radius) < 1.0) { // Check if the point is close to the circle's radius
				my_mlx_pixel_put(img, x, y, color);
			}
		}
	}
}

void	draw_triangle(t_data *img, int x0, int y0, int x1, int y1, int x2, int y2, int color) {
	// Drawing the edges of the triangle
	// You can replace this with an actual triangle drawing algorithm (e.g., Bresenham's algorithm)
	// For simplicity, drawing lines between each pair of points
	// Draw line between (x0, y0) and (x1, y1)
	// Replace this logic with an actual triangle drawing algorithm
	// e.g., Bresenham's algorithm or midpoint algorithm
	for (int x = x0; x <= x1; x++) {
		int y = y0 + (y1 - y0) * (x - x0) / (x1 - x0);
		my_mlx_pixel_put(img, x, y, color);
	}

	// Draw line between (x1, y1) and (x2, y2)
	for (int x = x1; x <= x2; x++) {
		int y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
		my_mlx_pixel_put(img, x, y, color);
	}

	// Draw line between (x2, y2) and (x0, y0)
	for (int x = x2; x <= x0; x++) {
		int y = y2 + (y0 - y2) * (x - x2) / (x0 - x2);
		my_mlx_pixel_put(img, x, y, color);
	}
}


void	draw_hexagon_outline(t_data *img, int centerX, int centerY, int size, int color) {
	double angle, x, y;

	for (int i = 0; i < 6; i++) {
		angle = M_PI / 3.0 * i; // 60 degrees between each point
		x = centerX + size * cos(angle);
		y = centerY + size * sin(angle);

		// Draw lines between each pair of points to form the hexagon
		int next_i = (i + 1) % 6;
		double next_x = centerX + size * cos(M_PI / 3.0 * next_i);
		double next_y = centerY + size * sin(M_PI / 3.0 * next_i);
		int steps = (int)fmax(fabs(next_x - x), fabs(next_y - y));
		for (int step = 0; step <= steps; step++) {
			double interp_x = x + (next_x - x) * step / steps;
			double interp_y = y + (next_y - y) * step / steps;
			my_mlx_pixel_put(img, (int)interp_x, (int)interp_y, color);
		}
	}
}


int	main(void) {
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1300, 700, "Shapes");
	img.img = mlx_new_image(mlx, 1300, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	// Draw a square
	draw_square(&img, 100, 100, 100, 0x00FF00); // Green

	// Draw a circle
	draw_circle(&img, 400, 200, 50, 0xFF0000); // Red

    draw_circle_outline(&img, 400, 200, 50, 0xFFFFFF);

	// Draw a triangle
	draw_triangle(&img, 600, 100, 700, 50, 800, 150, 0x0000FF); // Blue

	// Draw a hexagon
    draw_hexagon_outline(&img, 1000, 300, 50, 0xFFFF00);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
