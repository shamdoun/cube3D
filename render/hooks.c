/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:13:10 by shamdoun          #+#    #+#             */
/*   Updated: 2024/09/25 19:22:36 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	rotate_angle(t_player *p, int value)
{
	p->angle += value;
	if (p->angle >= 360)
		p->angle -= 360;
	else if (p->angle < 0)
		p->angle += 360;
}

void	update_map(t_map *m)
{
	mlx_delete_image(m->interface->mlx_ptr, m->interface->new_img);
	m->interface->new_img = mlx_new_image(m->interface->mlx_ptr,
			WIDTH * BLOCK_W, BLOCK_L * HEIGHT);
	draw_3d_walls(m);
	draw_mini_map(m);
	mlx_image_to_window(m->interface->mlx_ptr, m->interface->new_img, 0, 0);
}

void	terminate_game(t_map *m)
{
	mlx_delete_image(m->interface->mlx_ptr, m->interface->new_img);
	mlx_close_window(m->interface->mlx_ptr);
	mlx_terminate(m->interface->mlx_ptr);
	exit(1);
}

void	key_func(void *param)
{
	t_map	*m;

	m = (t_map *)param;
	if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_RIGHT))
		rotate_angle(m->player, -2);
	if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_LEFT))
		rotate_angle(m->player, 2);
	if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_D))
		move_right(m->player);
	if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_A))
		move_left(m->player);
	if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_W))
		move_up(m->player);
	if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_S))
		move_down(m->player);
	if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_ESCAPE))
		terminate_game(m);
	update_map(m);
}
