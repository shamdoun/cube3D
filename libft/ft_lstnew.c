/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:28:27 by shamdoun          #+#    #+#             */
/*   Updated: 2024/09/25 19:28:39 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

t_ray	*ft_lstnew(double x)
{
	t_ray	*n_node;

	n_node = (t_ray *)malloc(sizeof(t_ray));
	if (!n_node)
		return (NULL);
	n_node ->angle = x;
	n_node -> next = NULL;
	return (n_node);
}
