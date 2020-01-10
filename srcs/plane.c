/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 21:54:26 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/10 11:10:53 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Plane <origin> <color>
*/

void	set_plane(char **words, t_rtv1 *r)
{
	t_shape		*shape;
	t_plane		*plane;
	t_shape		*elt;

	shape = (t_shape*)malloc(sizeof(t_shape));
	plane = (t_plane*)malloc(sizeof(t_plane));
	plane->origin = get_vect_from_str(words[1]);
	plane->color = get_color_from_str(words[2]);
	plane->tran = get_vect_from_str(words[3]);
	plane->rot = get_vect_from_str(words[4]);
	shape->shape = plane;
	shape->id = 2;
	shape->next = NULL;
	elt = r->shape;
	if (r->shape == NULL)
		r->shape = shape;
	else
	{
		while (elt->next != NULL)
			elt = elt->next;
		elt->next = shape;
	}
}
