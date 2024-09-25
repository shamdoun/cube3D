/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:17:49 by shamdoun          #+#    #+#             */
/*   Updated: 2024/09/25 21:41:18 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int mapValues[10][21] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

// void	ft_lstadd_back(t_ray **lst, t_ray *new)
// {
// 	t_ray	*head;

// 	if (!lst || !new)
// 		return ;
// 	head = *lst;
// 	if (!head)
// 		*lst = new;
// 	else
// 	{
// 		while (head -> next)
// 			head = head -> next;
// 		head -> next = new;
// 	}
// }

// t_ray	*ft_lstnew(double x)
// {
// 	t_ray	*n_node;

// 	n_node = (t_ray *)malloc(sizeof(t_ray));
// 	if (!n_node)
// 		return (NULL);
// 	n_node ->angle = x;
// 	n_node -> next = NULL;
// 	return (n_node);
// }

// void	draw_mini_map(t_map *m)
// {
// 	draw_map(m->interface->new_img);
// 	draw_player(m);
// }

// void	init_map_values(t_map *map3d)
// {
// 	map3d->type = "3d map";
// 	map3d->player = malloc(sizeof(t_player));
// 	if (!map3d->player)
// 		exit (1);
// 	map3d->player->x_p = 17 * BLOCK_W + 40;
// 	map3d->player->y_p = 4 * BLOCK_L + 40;
// 	map3d->player->angle = 180;
// 	map3d->player->rotation_speed = 2;
// 	map3d->interface = malloc(sizeof(t_map));
// 	if (!map3d->interface)
// 		exit (1);
// 	map3d->interface->mlx_ptr = mlx_init(WIDTH * BLOCK_W,
// 			HEIGHT * BLOCK_L, "overall_map", false);
// 	if (!map3d->interface->mlx_ptr)
// 		exit (1);
// 	map3d->interface->new_img = mlx_new_image(map3d->interface->mlx_ptr,
// 			WIDTH * BLOCK_W, BLOCK_L * HEIGHT);
// }

// void	draw_3d_map(void)
// {
// 	t_map	*map3d;

// 	map3d = (t_map *)malloc(sizeof(t_map));
// 	if (!map3d)
// 		exit (1);
// 	init_map_values(map3d);
// 	draw_map(map3d->interface->new_img);
// 	draw_3d_walls(map3d);
// 	mlx_image_to_window(map3d->interface->mlx_ptr,
// 		map3d->interface->new_img, 0, 0);
// 	mlx_loop_hook(map3d->interface->mlx_ptr, &key_func, map3d);
// 	mlx_loop(map3d->interface->mlx_ptr);
// 	mlx_terminate(map3d->interface->mlx_ptr);
// }

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	draw_3d_map();
	return (1);
}
