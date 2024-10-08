/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:52:59 by shamdoun          #+#    #+#             */
/*   Updated: 2024/09/26 12:48:29 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

extern int mapValues[20][21];

int	mouvement_is_blocked(int map_y, int map_x, double angle)
{
	if (mapValues[map_y][map_x] == 1 || (!ray_is_facing_down(angle)
			&& ray_is_facing_left(angle) && (mapValues[map_y][map_x + 1] == 1
					&& mapValues[map_y + 1][map_x] == 1)) ||
		(!ray_is_facing_down(angle) && !ray_is_facing_left(angle)
				&& (mapValues[map_y][map_x - 1] == 1
				&& mapValues[map_y + 1][map_x] == 1)) ||
		(ray_is_facing_down(angle) && ray_is_facing_left(angle)
				&& (mapValues[map_y][map_x + 1] == 1
				&& mapValues[map_y - 1][map_x] == 1)))
		return (1);
	return (0);
}

void	move_up(t_player *p)
{
	double	old_x;
	double	old_y;

	old_x = p->x_p;
	old_y = p->y_p;
	p->x_p = p->x_p + cos(-p->angle * (M_PI / 180)) * 4;
	p->y_p = p->y_p + sin(-p->angle * (M_PI / 180)) * 4;
	if (wall_contact(p))
	{
		p->x_p = old_x;
		p->y_p = old_y;
	}
}

void	move_down(t_player *p)
{
	double	old_x;
	double	old_y;

	old_x = p->x_p;
	old_y = p->y_p;
	p->x_p = p->x_p + cos(-p->angle * (M_PI / 180)) * -4;
	p->y_p = p->y_p + sin(-p->angle * (M_PI / 180)) * -4;
	if (wall_contact(p))
	{
		p->x_p = old_x;
		p->y_p = old_y;
	}
}

void	move_right(t_player *p)
{
	double	old_x;
	double	old_y;

	old_x = p->x_p;
	old_y = p->y_p;
	p->x_p = p->x_p + cos(-p->angle * (M_PI / 180) + (M_PI / 2)) * 4;
	p->y_p = p->y_p + sin(-p->angle * (M_PI / 180) + (M_PI / 2)) * 4;
	if (wall_contact(p))
	{
		p->x_p = old_x;
		p->y_p = old_y;
	}
}

void	move_left(t_player *p)
{
	double	old_x;
	double	old_y;

	old_x = p->x_p;
	old_y = p->y_p;
	p->x_p = p->x_p + cos(-p->angle * (M_PI / 180) - (M_PI / 2)) * 4;
	p->y_p = p->y_p + sin(-p->angle * (M_PI / 180) - (M_PI / 2)) * 4;
	if (wall_contact(p))
	{
		p->x_p = old_x;
		p->y_p = old_y;
	}
}
