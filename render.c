/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:18:04 by shamdoun          #+#    #+#             */
/*   Updated: 2024/09/23 20:18:09 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

extern int mapValues[10][21];

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// void draw_direction(t_map *map, int x, int y, double angle)
// {
//     int line_length = 402; // Length of the line
//     int x1, y1;
//     int dx, dy, sx, sy, err, e2;

//     // Calculate the endpoint of the line based on the angle and length
//     x1 = x + cos(angle * (M_PI / 180) ) * line_length;
//     y1 = y + sin(angle * (M_PI / 180) ) * line_length;

//     dx = abs(x1 - x);
//     dy = abs(y1 - y);
//     sx = (x < x1) ? 1 : -1;
//     sy = (y < y1) ? 1 : -1;
//     err = dx - dy;

//     while (1) {
//         mlx_put_pixel(map->interface->new_img, x, y, get_rgba(0, 0, 255, 255));
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

// void	draw_rays(t_map *map)
// {
//     double a_begin = map->player->angle + 30;
//     double a_end = map->player->angle - 30;
//     double steps = 60.0 / (80 * 10);

//     while (a_begin > a_end)
//     {
//         draw_direction(map, map->player->x_p, map->player->y_p, a_begin);
//         a_begin -= steps;
//     }

// }

void	draw_map(mlx_image_t *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			draw_block(img, (i + 1) * (BLOCK_L),
				(j + 1) * (BLOCK_W), mapValues[i][j]);
			j++; 
		}
		i++;
	}
}

void	draw_block(mlx_image_t *img, int x, int y, int value)
{
	uint32_t	color;
	int			i;
	int			j;

	if (value == 1)
		color = get_rgba(0, 0, 0, 200);
	else
		color = get_rgba(255, 255, 255, 255);
	i = 0;
	while (i < BLOCK_W - 1)
	{
		j = 0;
		while (j < BLOCK_L - 1)
		{
			mlx_put_pixel(img, (y + j) / 4, (x + i) / 4, color);
			j++;
		}
		i++;
	}
}

void	my_put_mlx(t_map *map, int x, int y)
{
	mlx_put_pixel(map->interface->new_img,
		x / 4, y / 4, get_rgba(0, 0, 255, 255));
}

void	draw_circle(t_map *map, int x_center, int y_center, int radius)
{
	int	dx;
	int	dy;
	int	i;
	int	j;

	i = 0;
	while (i <= radius * 2)
	{
		dx = i - radius;
		j = 0;
		while (j <= radius * 2)
		{
			dy = j - radius;
			if (dx * dx + dy * dy <= radius * radius)
				my_put_mlx(map, (x_center + dx), (y_center + dy));
			j++;
		}
		i++;
	}
}

void	draw_player(t_map *map)
{
	int	x_center;
	int	y_center;
	int	radius;

	x_center = (map->player->x_p) + BLOCK_W;
	y_center = (map->player->y_p) + BLOCK_L;
	radius = 10;
	draw_circle(map, x_center, y_center, radius);
	apply_dda_algorithm(map);
}
