#include "cube3D.h"

extern int  mapValues[10][21];

long calculate_magnitude(t_player *player, int x, int y)
{
	x = x - player->x_p;
	y = y - player->y_p;
    // printf("distance x=%d y=%d\n", x, y);
	return (sqrt(x * x + y * y));
}

long	find_vertical_distance(t_map *m, double angle)
{
	int x_inter;
	int y_inter;
	int ax;
	int ay;

    if (angle == 90 || angle == 270)
        return (0);
	ax = BLOCK_W;
	ay = ax * tan(angle * (M_PI / 180));
	
    //first inter
	if (angle < 180 || angle > 270)
		x_inter = floor(m->player->y_p / BLOCK_L) * BLOCK_L + BLOCK_L;
	else
		x_inter = floor(m->player->y_p / BLOCK_L) * BLOCK_L - 1;
	y_inter = m->player->y_p + ((m->player->x_p - x_inter) * tan(angle * (M_PI / 180)));
	while ((x_inter >= 0) && (x_inter <= BLOCK_W * 10) && (y_inter >= 0) && (y_inter <= BLOCK_L * 21))
	{
		if (mapValues[(int)floor((m->player->y_p) / 80)][(int)floor((m->player->x_p) / 80)] == 1)
			break;
		x_inter += (angle < 90 || angle > 270 ) ? ax : -ax;
		y_inter += ay;
	}
    printf("wall hit %d %d\n", x_inter, y_inter);
	return (calculate_magnitude(m->player, x_inter, y_inter));
}


long	find_horizontal_distance(t_map *m, double angle)
{
    double x_inter;
    double y_inter;
    double ax;
    double ay;
    double rad_angle = angle * (M_PI / 180);
    double tan_angle = tan(rad_angle);
    int hit;

    if (tan_angle == 0)
        return 0;

    hit = 1;
    ay = BLOCK_L;
    ax = ay / tan_angle;
    // ax *= (angle < 90 && angle > 270 && ax < 0) ? -1 : 1;
    // ax *= (angle > 90 && angle < 270 && ax > 0) ? -1 : 1;
    printf("value of ax %f ay %f\n", ax, ay);
    // First intersection
    if (angle > 180)
        y_inter = floor(m->player->y_p / BLOCK_L) * BLOCK_L + BLOCK_L;
    else
        y_inter = floor(m->player->y_p / BLOCK_L) * BLOCK_L - 1;

    x_inter = m->player->x_p + (-m->player->y_p + y_inter) / tan_angle;

    while ((x_inter >=0) && (y_inter >= 0) && (x_inter <= BLOCK_W * 21) && (y_inter <= (BLOCK_L * 10)))
    {
        int map_x = (int)floor(x_inter / BLOCK_W);
        int map_y = (int)floor(y_inter / BLOCK_L);

        if (mapValues[map_y][map_x] == 1)
            break;

        x_inter = x_inter + ax;
        y_inter = y_inter + ((angle > 180) ? ay : -ay);
    }
    printf("wall hit %f %f %f %f\n", x_inter, y_inter, floor(x_inter / 80), floor(y_inter / 80));
    return calculate_magnitude(m->player, x_inter, y_inter);
}

void apply_dda_algorithm(t_map *m)
{
    long	h_distance;
    // long	v_distance;
    double a_begin = m->player->angle + 30;
    // double a_end = m->player->angle - 30;
    double steps = 3;
    int i = 0;

    printf("angle begins at %f\n", a_begin);
    
    while (i < 60)
    {
        if (a_begin < 0)
            a_begin += 360;
        if (a_begin >= 360)
            a_begin -= 360;
        printf("angle is %f\n",a_begin);
		h_distance = find_horizontal_distance(m, a_begin);
		// v_distance = find_vertical_distance(m, a_begin);
        //draw_direction_w(m, a_begin, min(h_distance, v_distance));
        // printf("lowest direction is %ld\n", MIN(h_distance, v_distance));
		a_begin -= steps;
        i++;
    }
}