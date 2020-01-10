/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:06:52 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/10 10:37:21 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	cone <centre> <diameter> <color>
*/

void	set_cone(char **words, t_rtv1 *r)
{
	t_shape		*shape;
	t_cone		*cone;
	t_shape		*elt;

	shape = (t_shape*)malloc(sizeof(t_shape));
	cone = (t_cone*)malloc(sizeof(t_cone));
	cone->origin = get_vect_from_str(words[1]);
	cone->radius = atof(words[2]);
	cone->color = get_color_from_str(words[3]);
	cone->tran = get_vect_from_str(words[4]);
	cone->rot = get_vect_from_str(words[5]);
	shape->shape = cone;
	shape->id = 4;
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
