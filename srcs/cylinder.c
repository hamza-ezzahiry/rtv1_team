/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 21:27:40 by hezzahir          #+#    #+#             */
/*   Updated: 2020/02/02 11:38:02 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Cylindre <origin> <raduis> <height> <axis> <color> <translation> <rotation>
*/

void			cylindre_rot_tran(t_cylindre *cylindre, char *s1, char *s2)
{
	cylindre->tran = get_vect_from_str(s1);
	cylindre->rot = get_vect_from_str(s2);
	cylindre->origin = trans(cylindre->origin, cylindre->tran);
	cylindre->axis = rotate(cylindre->axis, cylindre->rot);
}

void			set_cylindre(char **words, t_rtv1 *r)
{
	t_shape		*shape;
	t_cylindre	*cylindre;
	t_shape		*elt;

	shape = (t_shape*)ft_memalloc(sizeof(t_shape));
	cylindre = (t_cylindre*)ft_memalloc(sizeof(t_cylindre));
	cylindre->origin = get_vect_from_str(words[1]);
	cylindre->radius = ft_atof(words[2]);
	cylindre->height = ft_atof(words[3]);
	cylindre->axis = get_vect_from_str(words[4]);
	cylindre->color = get_color_from_str(words[5]);
	cylindre_rot_tran(cylindre, words[6], words[7]);
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

void			cylindre_checker(t_rtv1 *r, t_cylindre cylindre)
{
	t_light	*light;
	double	dist;

	light = r->light;
	while (light)
	{
		dist = distance(light->origin, cylindre.origin);
		if (dist < cylindre.radius * cylindre.radius)
			light->intensity = 0;
		light = light->next;
	}
}
