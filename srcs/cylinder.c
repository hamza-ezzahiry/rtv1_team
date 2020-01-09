/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 21:27:40 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/08 22:09:39 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Cylindre <origin> <raduis> <height> <color>
*/

void		set_cylindre(char **words, t_rtv1 *r)
{
	t_shape		*shape;
	t_cylindre	*cylindre;
	t_shape		*elt;

	shape = (t_shape*)malloc(sizeof(t_shape));
	cylindre = (t_cylindre*)malloc(sizeof(t_cylindre));
	cylindre->origin = get_vect_from_str(words[1]);
	cylindre->radius = atof(words[2]);
	cylindre->height = atof(words[3]);
	cylindre->color = get_color_from_str(words[4]);
	shape->shape = cylindre;
	shape->id = 3;
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