#include <mlx.h>
#include <math.h>
#include <stdlib.h>

int get_gradient_color(int start_color, int end_color, double t) {
    int red = start_color / 65536 + t * (end_color / 65536 - start_color / 65536);
    int green = (start_color / 256) % 256 + t * ((end_color / 256) % 256 - (start_color / 256) % 256);
    int blue = start_color % 256 + t * (end_color % 256 - start_color % 256);
    return red * 65536 + green * 256 + blue;
}

void draw_gradient_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int start_color, int end_color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    int current_color;

    while (1) {
        current_color = get_gradient_color(start_color, end_color, (double)(x1 - x0) / dx); // Calculate color for current point
        mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, current_color);

        if (x0 == x1 && y0 == y1) {
            break; // Done
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// 0,0xFFFFFF 0,0xd5aaaa

int main(void) {
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 500, 500, "Gradient Example");

    // ... (set up mlx, window, etc.)
    int start_color = 0xFFFFFF;  // Blue
    int end_color = 0xFF;    // Red
    draw_gradient_line(mlx, win, 100, 100, 300, 200, start_color, end_color);
    // ...

    mlx_loop(mlx);

    return 0;
}