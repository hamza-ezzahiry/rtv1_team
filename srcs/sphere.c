/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 11:59:15 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/10 11:13:55 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Sphare
*/

void		set_sphere(char **words, t_rtv1 *r)
{
	t_shape		*shape;
	t_sphere	*sphere;
	t_shape		*elt;

	shape = (t_shape*)malloc(sizeof(t_shape));
	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	sphere->origin = get_vect_from_str(words[1]);
	sphere->radius = atof(words[2]);
	sphere->color = get_color_from_str(words[3]);
	sphere->tran = get_vect_from_str(words[4]);
	sphere->rot = get_vect_from_str(words[5]);
	shape->shape = sphere;
	shape->id = 1;
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
