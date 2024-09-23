/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_algorithms.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:18:30 by shamdoun          #+#    #+#             */
/*   Updated: 2024/09/23 22:18:57 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

extern int  mapValues[10][21];

long	calculate_magnitude(t_player *player, double x, double y)
{
	double	dx;
	double	dy;

	dx = fabs(x - player->x_p);
	dy = fabs(y - player->y_p);
	return ((long)sqrt((dx * dx) + (dy * dy)));
}


int	ray_is_facing_down(double angle)
{
	return (angle > 180 && angle < 360);
}

int	ray_is_facing_left(double angle)
{
	return (angle > 90 && angle < 270);
}

int	check_if_wall_hits(int map_y, int map_x, double angle)
{
	if (mapValues[map_y][map_x] == 1 || (!ray_is_facing_down(angle)
			&& ray_is_facing_left(angle) && (mapValues[map_y][map_x + 1] == 1
					&& mapValues[map_y + 1][map_x] == 1) ||
		!ray_is_facing_down(angle) && !ray_is_facing_left(angle)
				&& (mapValues[map_y][map_x - 1] == 1
				&& mapValues[map_y + 1][map_x] == 1)) ||
		ray_is_facing_down(angle) && ray_is_facing_left(angle)
				&& (mapValues[map_y][map_x + 1] == 1
				&& mapValues[map_y - 1][map_x] == 1))
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

void initialise_params_for_vert_calc(t_ray_calc *vertical, double angle)
{
	vertical->tan_angle = tan(angle * (M_PI / 180));
	vertical->verif_x = angle > 90 && angle < 270;
	vertical->verif_y = angle > 180 && angle < 360;
	vertical->ax = BLOCK_W * (vertical->verif_x ? -1 : 1);
	vertical->ay = BLOCK_W * tan(angle * (M_PI / 180));
	vertical->angle = angle;
	vertical->ay *= (!vertical->verif_y
		&& vertical->ay > 0) ? -1 : 1;
	vertical->ay *= (vertical->verif_y
		&& vertical->ay < 0) ? -1 : 1;
}

void initialise_params_for_hor_calc(t_ray_calc *hor, double angle)
{
	hor->tan_angle = tan(angle * (M_PI / 180));
	hor->verif_y = angle > 180 && angle < 360;
	hor->verif_x = angle > 90 && angle < 270;
	hor->ay = BLOCK_L * (hor->verif_y ? 1 : -1);  
	hor->ax = BLOCK_L / hor->tan_angle;
	hor->ax *= (hor->verif_x && hor->ax > 0) ? -1 : 1;
	hor->ax *= (!hor->verif_x && hor->ax < 0) ? -1 : 1;
}

void update_angle(double *angle)
{
	if ((*angle) < 0)
		(*angle) += 360;
	if ((*angle) >= 360)
		(*angle) -= 360;
}

void	init_first_vertical_inter(t_ray_calc *vertical, t_map *m,
	double *x_inter, double *y_inter)
{
	if (!vertical->verif_x)
		(*x_inter) = floor(m->player->x_p / BLOCK_L) * BLOCK_L + BLOCK_L;
	else
		(*x_inter) = floor(m->player->x_p / BLOCK_L) * BLOCK_L - 1;
	(*y_inter) = m->player->y_p
		+ ((m->player->x_p - (*x_inter)) * tan(vertical->angle * (M_PI / 180)));

}

void	init_first_hor_inter(t_ray_calc *hor, t_map *m,
	double *x_inter, double *y_inter)
{
	if (hor->verif_y)
		(*y_inter) = floor(m->player->y_p / BLOCK_L) * BLOCK_L + BLOCK_L;
	else
		(*y_inter) = floor(m->player->y_p / BLOCK_L) * BLOCK_L - 1;
	(*x_inter) = m->player->x_p
		+ (m->player->y_p - (*y_inter)) / hor->tan_angle;

}

long	find_vertical_distance_v1(t_map *m, t_ray **v, double angle)
{
	double		x_inter;
	double		y_inter;	
	t_ray_calc	*vertical;
	int			map_x;
	int			map_y;

	update_angle(&angle);
	vertical = malloc(sizeof(t_ray_calc));
	initialise_params_for_vert_calc(vertical, angle);
	init_first_vertical_inter(vertical, m, &x_inter, &y_inter);
	while ((fabs(x_inter) <= BLOCK_W * 21) && (fabs(y_inter) <= (BLOCK_L * 10)))
	{
		map_x = (int)floor(fabs(x_inter) / BLOCK_W);
		map_y = (int)floor(fabs(y_inter) / BLOCK_L);
		if (map_x < 21 && map_y < 10 && check_if_wall_hits(map_y, map_x, angle))
			break ;
		x_inter = x_inter + vertical->ax;
		y_inter = y_inter + vertical->ay;
	}
	(*v)->x = x_inter;
	(*v)->bitmap_offset = y_inter;
	return (calculate_magnitude(m->player, x_inter, y_inter));
}

long	find_horizontal_distance_v1(t_map *m, t_ray **h, double angle)
{
	double		x_inter;
	double		y_inter;
	t_ray_calc	*horiz;
	int			map_x;
	int			map_y;

	update_angle(&angle);
	horiz = malloc(sizeof(t_ray_calc));
	initialise_params_for_hor_calc(horiz, angle);
	init_first_hor_inter(horiz, m, &x_inter, &y_inter);
	while (x_inter >= 0 && y_inter >= 0
		&& x_inter <= (BLOCK_W * 21) && y_inter <= (BLOCK_L * 10))
	{
		map_x = (int)floor((fabs(x_inter)) / BLOCK_W);
		map_y = (int)floor(fabs(y_inter) / BLOCK_L);
		if (map_x < 21 && map_y < 10 && check_if_wall_hits(map_y, map_x, angle))
			break ;
		x_inter = x_inter + horiz->ax;
		y_inter = y_inter + horiz->ay;
	}
	(*h)->x = x_inter;
	(*h)->bitmap_offset = x_inter;
	return (calculate_magnitude(m->player, x_inter, y_inter));

}

void	init_vector_values(t_line *line, t_map *m,
		long h_distance, double angle)
{
	line->x = m->player->x_p + BLOCK_W;
	line->y = m->player->y_p + BLOCK_L;

	line->line_length = h_distance;

	line->x1 = line->x + cos(-angle * (M_PI / 180)) * line->line_length;
	line->y1 = line->y + sin(-angle * (M_PI / 180)) * line->line_length;

	line->dx = abs(line->x1 - line->x);
	line->dy = abs(line->y1 - line->y);
    line->sx = (line->x < line->x1) ? 1 : -1;
    line->sy = (line->y < line->y1) ? 1 : -1;
	line->err = line->dx - line->dy;
}


void	draw_direction_w(t_map *m, double angle, long h_distance)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		exit(1);
	init_vector_values(line, m, h_distance, angle);
	while (1)
	{
		mlx_put_pixel(m->interface->new_img,
			line->x / 4, line->y / 4, get_rgba(0, 0, 255, 255));
		if (line->x == line->x1 && line->y == line->y1)
			break ;
		line->e2 = line->err * 2;
		if (line->e2 > -(line->dy))
		{
			line->err -= line->dy;
			line->x += line->sx;
		}
		if (line->e2 < line->dx)
		{
			line->err += line->dx;
			line->y += line->sy;
		}
	}
}

// void	draw_direction_ve(t_map *m, double angle, long h_distance)
// {
//     int line_length = h_distance; // Length of the line
//     int x1, y1;
//     int dx, dy, sx, sy, err, e2;
//     int x, y;

//     x = m->player->x_p + BLOCK_W;
//     y = m->player->y_p + BLOCK_L;

//     // Calculate the endpoint of the line based on the angle and length
//     x1 = x + cos(-angle * (M_PI / 180)) * line_length;
//     y1 = y + sin(-angle * (M_PI / 180)) * line_length;

//     dx = abs(x1 - x);
//     dy = abs(y1 - y);
//     sx = (x < x1) ? 1 : -1;
//     sy = (y < y1) ? 1 : -1;
//     err = dx - dy;

//     while (1) {
//         mlx_put_pixel(m->interface->new_img, x / 4, y / 4, get_rgba(0, 0, 255, 255));
//         if (x == x1 && y == y1) break;
//         e2 = err * 2;
//         if (e2 > -dy) {
//             err -= dy;
//             x += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             y += sy;
//         }
//     }
// }

void	apply_dda_algorithm(t_map *m)
{
	long	h_distance;
	long	v_distance;
	double	a_begin;
	double	a_end;
	double	steps;

	a_begin = m->player->angle + 30;
	a_end = m->player->angle - 30;
	steps = 60.0 / (21 * 10);
	while (a_begin > a_end)
	{
		h_distance = find_horizontal_distance(m, a_begin);
		v_distance = find_vertical_distance(m, a_begin);
		draw_direction_w(m, a_begin, MIN(h_distance, v_distance));
		a_begin -= steps;
	}
}


int	convertPixelColor(uint32_t color, int format)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;

	alpha = color >> 24;
	blue = color >> 16 & 0xFF;
	green = color >> 8 & 0xFF;
	red = color & 0xFF;
	return (get_rgba(red, green, blue, alpha));
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
    double steps = 60.0 / (WIDTH * BLOCK_W);
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
    mlx_texture_t *texture = mlx_load_png("textures/wood.png");
    // printf("width %d\n", sky->width);
    uint32_t *arr = (uint32_t *)texture->pixels;
    if (!texture)
        perror("failed to open texture!");
    
    // printf("width %d height %d\n", texture->width, texture->height);
    w = malloc(sizeof(t_wall));
    if (!w)
        exit(1);
    x = 0;
    int y;
    // int steps2 = 211 / (21 * 80);
    long distance_to_projection = (WIDTH * BLOCK_W / 2) / tan(FOV / 2 * (M_PI / 180));
    // for (int w = 0; w < texture->width; w++)
    // {
    //     for (int g = 0; g < texture->height; g++)
    //     {
    //         mlx_put_pixel(m->interface->new_img, g, w, arr[w * texture->width + g]);
    //     }
    // }
    // printf("value is %d\n", distance_to_projection);
    while (rays) {
        float distance = rays->distance;

        //fixing fish distortion
        distance = cos((m->player->angle - rays->angle) * (M_PI / 180)) * distance;
        
        //wall height
        double wall_height = (distance_to_projection * BLOCK_L) / distance;
        
        int wall_top = ((BLOCK_L * HEIGHT) / 2) - ((wall_height /  2));
        if (wall_top <= 0)
            wall_top = 0;
        int wall_bot = ((BLOCK_L * HEIGHT) / 2) + ((wall_height / 2));
        if (wall_bot >= HEIGHT * BLOCK_L)
            wall_bot = HEIGHT * BLOCK_L;
        // Draw vertical line in the image buffer

        int color = 255;
        // for (int t = 0; t < wall_top; t++)
        // {   
        //     mlx_put_pixel(m->interface->new_img, x, y, get_rgba(240, 25, 56, 200));
        // }
        int intensity = rays->hit_vertical ? 70 : 100;
        double offset_x;
        double offset_x1;
        double offset_y;
        double offset_y1;
    
        offset_x = (int)((rays->bitmap_offset) * (texture->width / BLOCK_W)) % (texture->width);
        if (offset_x < 0)
            offset_x = 0;


        double scaling_factor;
        double y_sky;
        double text_pos;

        scaling_factor = ((double)texture->height / wall_height);
        // scaling_for_sky = ((double)sky->height / (wall-));
        // printf("scaling factor %f\n", scaling_factor);
                uint8_t start_r = 135, start_g = 206, start_b = 235; // Light blue
                uint8_t end_r = 0, end_g = 0, end_b = 139; // Dark blue
        for (y = 0; y < (HEIGHT * BLOCK_L); y++)
        {
            if (y < wall_top)
            {

                        float t = (float)y / (HEIGHT * BLOCK_L);

        // Interpolate color values
                uint8_t r = (uint8_t)(start_r + (end_r - start_r) * t);
                uint8_t g = (uint8_t)(start_g + (end_g - start_g) * t);
                uint8_t b = (uint8_t)(start_b + (end_b - start_b) * t);

                mlx_put_pixel(m->interface->new_img, x, y, get_rgba(r,g ,b , 255));
                // offset_y1 += scaling_for_sky;
            } 
            if (y == wall_top)
            {
                offset_y = ((wall_top - (HEIGHT * BLOCK_L / 2) + (wall_height / 2)) * scaling_factor);
                if (offset_y < 0)
                    offset_y = 0;
                for (y = wall_top; y < wall_bot; y++)
                {
                    // int textY = (int)offset_y & (texture->height - 1);
                    // printf("offset x %f y %f\n", offset_x, offset_y);
                    // printf("offset_y %f\n", offset_y);
                    uint32_t color = arr[((int)offset_y * texture->width) + (int)offset_x];
                    // color = (color >> 1) & 8355711;
                    mlx_put_pixel(m->interface->new_img, x, y, convertPixelColor(color, 1));
                    offset_y += scaling_factor;
                    // float dist = (y - wall_top) / (float)(wall_bot - wall_top);
                }
            }
            if (y > wall_top)
            {
                mlx_put_pixel(m->interface->new_img, x, y, get_rgba(245, 222, 179, 255));
            }
        }
        rays = rays->next;
        x += 1;
    }
}
