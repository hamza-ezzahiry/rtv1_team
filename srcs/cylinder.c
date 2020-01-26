/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 21:27:40 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/26 17:22:47 by hezzahir         ###   ########.fr       */
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

	shape = (t_shape*)ft_memalloc(sizeof(t_shape));
	cylindre = (t_cylindre*)ft_memalloc(sizeof(t_cylindre));
	cylindre->origin = get_vect_from_str(words[1]);
	cylindre->radius = atof(words[2]);
	cylindre->height = atof(words[3]);
	cylindre->axis = get_vect_from_str(words[4]);
	cylindre->color = get_color_from_str(words[5]);
	cylindre->tran = get_vect_from_str(words[6]);
	cylindre->rot = get_vect_from_str(words[7]);
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
	cylindre->origin = trans(cylindre->origin, cylindre->tran);
	cylindre->axis = rotate(cylindre->axis, cylindre->rot);
}
