/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:32:54 by shamdoun          #+#    #+#             */
/*   Updated: 2024/09/26 12:47:36 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

extern int mapValues[20][21];

int	get_map_value(t_player *p, int x, int y)
{
	return (mapValues[(int)floor((p->y_p + y)
				/ BLOCK_L)][(int)floor((p->x_p + x) / BLOCK_L)]);
}

int	wall_contact(t_player *p)
{
	if (get_map_value(p, 0, -20) || get_map_value(p, 20, 0)
		|| get_map_value(p, -20, 0) || get_map_value(p, 0, 20)
		|| get_map_value(p, -20, 20) || get_map_value(p, -20, -20)
		|| get_map_value(p, 20, -20) || get_map_value(p, 20, 20))
		return (1);
	return (0);
}

void	init_map_values(t_map *map3d)
{
	map3d->type = "3d map";
	map3d->player = malloc(sizeof(t_player));
	if (!map3d->player)
		exit (1);
	map3d->player->x_p = 17 * BLOCK_W + 40;
	map3d->player->y_p = 4 * BLOCK_L + 40;
	map3d->player->angle = 180;
	map3d->player->rotation_speed = 2;
	map3d->interface = malloc(sizeof(t_map));
	if (!map3d->interface)
		exit (1);
	map3d->interface->mlx_ptr = mlx_init(WIDTH * BLOCK_W,
			HEIGHT * BLOCK_L, "overall_map", false);
	if (!map3d->interface->mlx_ptr)
		exit (1);
	map3d->interface->new_img = mlx_new_image(map3d->interface->mlx_ptr,
			WIDTH * BLOCK_W, BLOCK_L * HEIGHT);
}

void	draw_3d_map(void)
{
	t_map	*map3d;

	map3d = (t_map *)malloc(sizeof(t_map));
	if (!map3d)
		exit (1);
	init_map_values(map3d);
	draw_map(map3d->interface->new_img);
	draw_3d_walls(map3d);
	mlx_image_to_window(map3d->interface->mlx_ptr,
		map3d->interface->new_img, 0, 0);
	mlx_loop_hook(map3d->interface->mlx_ptr, &key_func, map3d);
	mlx_loop(map3d->interface->mlx_ptr);
	mlx_terminate(map3d->interface->mlx_ptr);
}
