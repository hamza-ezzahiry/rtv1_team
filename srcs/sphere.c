/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 11:59:15 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/05 13:14:25 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


/*
**	Sphare
*/

void		set_sphere(char **words, t_rtv1  *r)
{
	t_shape		*shape;
	t_sphere	*sphere;

	shape = (t_shape*)malloc(sizeof(t_shape));
	sphere = (t_sphere*)malloc(sizeof(t_sphere));

	sphere->origin = get_vect_from_str(words[1]);
	sphere->radius = atof(words[2]);
	sphere->color = get_color_from_str(words[3]);

	shape->shape = sphere;
	shape->id = 1;
	shape->next = NULL;

	t_shape *elt;
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
