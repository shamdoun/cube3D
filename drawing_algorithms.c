#include "cube3D.h"
#include <stdio.h>

extern int  mapValues[10][21];

long calculate_magnitude(t_player *player, double x, double y)
{
    // Compute the absolute differences in coordinates
    double dx = fabs(x - player->x_p);
    double dy = fabs(y - player->y_p);
    
    // Calculate the Euclidean distance
    return (long)sqrt((dx * dx) + (dy * dy));
}


int ray_is_facing_down(double angle)
{
    return (angle > 180 && angle < 360);
}
int ray_is_facing_left(double angle)
{
    return (angle > 90 && angle < 270);
}

int check_if_wall_hits(int map_y, int map_x, double angle)
{
    if (mapValues[map_y][map_x] == 1 || (!ray_is_facing_down(angle) && ray_is_facing_left(angle) && (mapValues[map_y][map_x + 1] == 1 && mapValues[map_y + 1][map_x] == 1) ||
        !ray_is_facing_down(angle) && !ray_is_facing_left(angle) && (mapValues[map_y][map_x - 1] == 1 && mapValues[map_y + 1][map_x] == 1)) ||
        ray_is_facing_down(angle) && ray_is_facing_left(angle) && (mapValues[map_y][map_x + 1] == 1 && mapValues[map_y - 1][map_x] == 1))
            return (1);
    return (0);
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
        // printf("ver intersection %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
        int map_x = (int)floor(fabs(x_inter) / BLOCK_W);
        int map_y = (int)floor(fabs(y_inter) / BLOCK_L);

        if (map_x < 21 && map_y < 10 && check_if_wall_hits(map_y, map_x, angle))
        {
            // printf("wall is hit!\n");
            break;
        }
        x_inter = x_inter + ax;
        y_inter = y_inter + ay;
	}
    // printf("wall hit ver %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
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

    while (x_inter >= 0 && y_inter >= 0 && x_inter <= (BLOCK_W * 21) && y_inter <= (BLOCK_L * 10))
    {
        // printf("hor intersection %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
        int map_x = (int)floor((fabs(x_inter)) / BLOCK_W);
        int map_y = (int)floor(fabs(y_inter) / BLOCK_L);

        if (map_x < 21 && map_y < 10 && check_if_wall_hits(map_y, map_x, angle))
        {
            // printf("wall is hit!\n");
            break;
        }
        x_inter = x_inter + ax;
        y_inter = y_inter + ay;
    }
    // printf("wall hit hor %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
    return calculate_magnitude(m->player, x_inter, y_inter);
}
long	find_vertical_distance_v1(t_map *m, t_ray **v, double angle)
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
        // printf("ver intersection %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
        int map_x = (int)floor(fabs(x_inter) / BLOCK_W);
        int map_y = (int)floor(fabs(y_inter) / BLOCK_L);

        if (map_x < 21 && map_y < 10 && check_if_wall_hits(map_y, map_x, angle))
        {
            // printf("wall is hit!\n");
            break;
        }
        x_inter = x_inter + ax;
        y_inter = y_inter + ay;
	}
    // printf("wall hit ver %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
        (*v)->x = x_inter;
        (*v)->bitmap_offset = (int)y_inter % 64;
	return (calculate_magnitude(m->player, x_inter, y_inter));
}


long	find_horizontal_distance_v1(t_map *m, t_ray **h, double angle)
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

    while (x_inter >= 0 && y_inter >= 0 && x_inter <= (BLOCK_W * 21) && y_inter <= (BLOCK_L * 10))
    {
        // printf("hor intersection %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
        int map_x = (int)floor((fabs(x_inter)) / BLOCK_W);
        int map_y = (int)floor(fabs(y_inter) / BLOCK_L);

        if (map_x < 21 && map_y < 10 && check_if_wall_hits(map_y, map_x, angle))
        {
            // printf("wall is hit!\n");
            break;
        }
        x_inter = x_inter + ax;
        y_inter = y_inter + ay;
    }
    // printf("wall hit hor %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
    (*h)->x = x_inter;
    (*h)->bitmap_offset = (int)x_inter % 64;
    return calculate_magnitude(m->player, x_inter, y_inter);
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
    double steps = 60.0 / (21 * 10);
    int i = 0;
    
    // printf("angle %f\n", a_begin);
    while (a_begin > a_end)
    {
        i++;
		h_distance = find_horizontal_distance(m, a_begin);
		v_distance = find_vertical_distance(m, a_begin);
        // draw_direction_w(m, a_begin, (v_distance));
        draw_direction_w(m, a_begin, MIN(h_distance, v_distance));
		a_begin -= steps;
    }
    printf("number of rays %d\n", i);
}

void draw_3d_walls(t_map *m)
{
    int x;
    t_wall *w;
    t_ray *rays;

    //measure all rays
    rays = malloc(sizeof(t_ray));
    if (!rays)
        exit (1);
    rays = NULL;
    t_ray	*h_ray;
    t_ray	*v_ray;
    double a_begin = m->player->angle + 30;
    double a_end = m->player->angle - 30;
    double steps = 60.0 / (WIDTH * 80);
    int i = 0;
    
    // printf("angle %f\n", a_begin);
    
    while (a_begin > a_end)
    {
        h_ray = malloc(sizeof(t_ray));
        h_ray->angle = a_begin;
        h_ray->next = NULL;
        v_ray = malloc(sizeof(t_ray));
        v_ray->angle = a_begin;
        v_ray->next = NULL;

		h_ray->distance = find_horizontal_distance_v1(m, &h_ray, a_begin);
		v_ray->distance = find_vertical_distance_v1(m, &v_ray, a_begin);
        if (h_ray->distance > v_ray->distance)
        {
            v_ray->hit_vertical = 1;
            ft_lstadd_back(&rays, v_ray);
        }
        else
        {
            h_ray->hit_vertical = 0;
            ft_lstadd_back(&rays, h_ray);
        }
        a_begin -= steps;
    }


    // //render all walls
    mlx_texture_t *texture = mlx_load_png("mossystone.png");
    w = malloc(sizeof(t_wall));
    if (!w)
        exit(1);
    x = 0;
    int y;
    int steps2 = 211 / (21 * 80);
    long distance_to_projection = (WIDTH * BLOCK_W / 2) / tan(FOV / 2 * (M_PI / 180));
    // printf("value is %d\n", distance_to_projection);
    while (rays) {
        float distance = rays->distance;

        //fixing fish distortion
        distance = cos((m->player->angle - rays->angle) * (M_PI / 180)) * distance;
        
        //wall height
        float wall_height = (distance_to_projection * BLOCK_L) / distance;
        
        int wall_top = ((80 * 10) / 2) - ((wall_height /  2));
        if (wall_top <= 0)
            wall_top = 12;
        int wall_bot = ((80 * 10) / 2) + ((wall_height / 2));
        if (wall_bot >= HEIGHT * 80)
            wall_bot = HEIGHT * 80 - 12;
        // Draw vertical line in the image buffer

        int color = 255;
        // for (int t = 0; t < wall_top; t++)
        // {   
        //     mlx_put_pixel(m->interface->new_img, x, y, get_rgba(240, 25, 56, 200));
        // }
        int intensity = rays->hit_vertical ? 70 : 100;
        for (y = 0; y < (HEIGHT * 80); y++)
        {
            if (y < wall_top)
                mlx_put_pixel(m->interface->new_img, x, y, get_rgba(240, 25, 56, 200));

            if (y == wall_top)
            {
                for (y = wall_top; y < wall_bot; y++)
                {
                    mlx_put_pixel(m->interface->new_img, x, y, get_rgba(color, color, color, intensity));
                }
            }
            if (y > wall_top)
               mlx_put_pixel(m->interface->new_img, x, y, get_rgba(144, 180, 169, 100));
        }
        rays = rays->next;
        x += 1;
    }
}
