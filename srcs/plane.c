/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 21:54:26 by hezzahir          #+#    #+#             */
/*   Updated: 2020/02/02 12:14:10 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Plane <origin> <color> <norme> <translation> <rotation>
*/

void	plane_rot_tran(t_plane *plane, char *s1, char *s2)
{
	plane->tran = get_vect_from_str(s1);
	plane->rot = get_vect_from_str(s2);
	plane->origin = trans(plane->origin, plane->tran);
	plane->norm = rotate(plane->norm, plane->rot);
}

void	set_plane(char **words, t_rtv1 *r)
{
	t_shape		*shape;
	t_plane		*plane;
	t_shape		*elt;

	shape = (t_shape*)ft_memalloc(sizeof(t_shape));
	plane = (t_plane*)ft_memalloc(sizeof(t_plane));
	plane->origin = get_vect_from_str(words[1]);
	plane->color = get_color_from_str(words[2]);
	plane->norm = get_vect_from_str(words[3]);
	plane_rot_tran(plane, words[4], words[5]);
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
	plane->origin = trans(plane->origin, plane->tran);
	plane->norm = rotate(plane->norm, plane->rot);
	r->is_okey[2] = '1';
}
