#include "cube3D.h"
#include <stdio.h>

extern int  mapValues[10][21];

long calculate_magnitude(t_player *player, double x, double y)
{
    // Compute the absolute differences in coordinates
    double dx = fabs(x - player->x_p);
    double dy = fabs(y - player->y_p);
    
    // Calculate the Euclidean distance
    return (long)sqrt(dx * dx + dy * dy);
}

long	find_vertical_distance(t_map *m, double angle)
{
    double x_inter;
    double y_inter;
    double ax;
    double ay;
    if (angle < 0)
        angle += 360;
    if (angle >= 360)
        angle -= 360;

    double rad_angle = angle * (M_PI / 180);
    double tan_angle = tan(rad_angle);
    double verif_y;
    double verif_x;

    verif_x = angle > 90 && angle < 270;
    verif_y = angle > 180 && angle < 360;
	ax = BLOCK_W * (verif_x ? -1 : 1);
	ay = BLOCK_W * tan(angle * (M_PI / 180));
    ay *= (!verif_y && ay > 0) ? -1 : 1;
    ay *= (verif_y && ay < 0) ? -1 : 1;

    // printf("value of ax %f ay %f\n", ax, ay);
    //first inter
	if (!verif_x)
		x_inter = floor(m->player->x_p / BLOCK_L) * BLOCK_L + BLOCK_L;
	else
		x_inter = floor(m->player->x_p / BLOCK_L) * BLOCK_L - 1;
	y_inter = m->player->y_p + ((m->player->x_p - x_inter) * tan(angle * (M_PI / 180)));
        // printf("before intersection %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
    while ((fabs(x_inter) <= BLOCK_W * 21) && (fabs(y_inter) <= (BLOCK_L * 10)))
	{
        // printf("intersection %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
        int map_x = (int)floor(fabs(x_inter) / BLOCK_W);
        int map_y = (int)floor(fabs(y_inter) / BLOCK_L);

        if (map_x < 21 && map_y < 10 && mapValues[map_y][map_x] == 1)
        {
            // printf("wall is hit!\n");
            break;
        }
        x_inter = x_inter + ax;
        y_inter = y_inter + ay;
	}
    // printf("wall hit %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
	return (calculate_magnitude(m->player, x_inter, y_inter));
}


long	find_horizontal_distance(t_map *m, double angle)
{
    double x_inter;
    double y_inter;
    double ax;
    double ay;
    if (angle < 0)
        angle += 360;
    if (angle >= 360)
        angle -= 360;

    double rad_angle = angle * (M_PI / 180);
    double tan_angle = tan(rad_angle);
    int verif_y;
    int verif_x;

    verif_y = angle > 180 && angle < 360;
    verif_x = angle > 90 && angle < 270;
    ay = BLOCK_L * (verif_y ? 1 : -1);
        
    ax = BLOCK_L / tan_angle;
    ax *= (verif_x && ax > 0) ? -1 : 1;
    ax *= (!verif_x && ax < 0) ? -1 : 1;

    // printf("value of ax %f ay %f\n", ax, ay);

    // First intersection
    if (verif_y)
        y_inter = floor(m->player->y_p / BLOCK_L) * BLOCK_L + BLOCK_L;
    else
        y_inter = floor(m->player->y_p / BLOCK_L) * BLOCK_L - 1;

    x_inter = m->player->x_p + (m->player->y_p - y_inter) / tan_angle;

    while ((fabs(x_inter) <= BLOCK_W * 21) && (fabs(y_inter) <= (BLOCK_L * 10)))
    {
        // printf("intersection %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
        int map_x = (int)floor(fabs(x_inter) / BLOCK_W);
        int map_y = (int)floor(fabs(y_inter) / BLOCK_L);

        if (map_x < 21 && map_y < 10 && mapValues[map_y][map_x] == 1)
        {
            // printf("wall is hit!\n");
            break;
        }
        x_inter = x_inter + ax;
        y_inter = y_inter + ay;
    }
    // printf("wall hit %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
    return calculate_magnitude(m->player, x_inter, y_inter);
}

int ray_is_facing_down(double angle)
{
    return (angle > 180 && angle < 360);
}

void draw_direction_w(t_map *m, double angle, long h_distance)
{
    int line_length = h_distance; // Length of the line
    int x1, y1;
    int dx, dy, sx, sy, err, e2;
    int x, y;

    x = m->player->x_p;
    y = m->player->y_p;

    // Calculate the endpoint of the line based on the angle and length
    x1 = x + cos(-angle * (M_PI / 180)) * line_length;
    y1 = y + sin(-angle * (M_PI / 180)) * line_length;

    dx = abs(x1 - x);
    dy = abs(y1 - y);
    sx = (x < x1) ? 1 : -1;
    sy = (y < y1) ? 1 : -1;
    err = dx - dy;

    while (1) {
        mlx_put_pixel(m->interface->new_img, x, y, get_rgba(0, 0, 255, 255));
        if (x == x1 && y == y1) break;
        e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

void apply_dda_algorithm(t_map *m)
{
    long	h_distance;
    long	v_distance;
    double a_begin = m->player->angle + 30;
    double a_end = m->player->angle - 30;
    double steps = 60.0 / (80 * 10);
    int i = 0;
    
    while (a_begin > a_end)
    {
		h_distance = find_horizontal_distance(m, a_begin);
		v_distance = find_vertical_distance(m, a_begin);
        draw_direction_w(m, a_begin, MIN(h_distance, v_distance));
		a_begin -= steps;
    }
}