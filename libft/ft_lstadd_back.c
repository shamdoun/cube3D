/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:27:55 by shamdoun          #+#    #+#             */
/*   Updated: 2024/09/25 21:46:01 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	ft_lstadd_back(t_ray **lst, t_ray *new)
{
	t_ray	*head;

	if (!lst || !new)
		return ;
	head = *lst;
	if (!head)
		*lst = new;
	else
	{
		while (head -> next)
			head = head -> next;
		head -> next = new;
	}
}
