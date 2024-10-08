/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:18:04 by shamdoun          #+#    #+#             */
/*   Updated: 2024/09/26 12:50:12 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

extern int mapValues[10][21];

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	my_put_mlx(t_map *map, int x, int y)
{
	mlx_put_pixel(map->interface->new_img,
		x / 4, y / 4, get_rgba(0, 0, 255, 255));
}

int	convert_pixel_to_color(uint32_t color)
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

void	draw_sky(t_map *m, int x, t_wall *w)
{
	int			y;
	t_gradient	*gradient;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;

	gradient = malloc(sizeof(t_gradient));
	init_gradient(gradient);
	y = 0;
	while (y < w->wall_top)
	{
		gradient->t = (float)y / (HEIGHT * BLOCK_L);
		r = (uint8_t)(gradient->start_r
				+ (gradient->end_r - gradient->start_r) * gradient->t);
		g = (uint8_t)(gradient->start_g
				+ (gradient->end_g - gradient->start_g) * gradient->t);
		b = (uint8_t)(gradient->start_b
				+ (gradient->end_b - gradient->start_b) * gradient->t);
		mlx_put_pixel(m->interface->new_img, x, y, get_rgba(r, g, b, 255));
		y++;
	}
	free(gradient);
}

void	draw_floor(t_wall *w, t_map *m, int x)
{
	int	y;

	y = w->wall_bot;
	while (y < (HEIGHT * BLOCK_L))
	{
		mlx_put_pixel(m->interface->new_img,
			x, y, get_rgba(245, 222, 179, 255));
		y++;
	}
}
