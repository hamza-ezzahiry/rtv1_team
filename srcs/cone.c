/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:06:52 by hezzahir          #+#    #+#             */
/*   Updated: 2020/02/08 19:20:45 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	cone <origin> <raduis> <height> <color> <axis vector> <translate> <rotation>
*/

void		add_rot_tran(t_rtv1 *r, t_cone *cone, char *s1, char *s2)
{
	cone->tran = get_vect_from_str(s1);
	cone->rot = get_vect_from_str(s2);
	cone->rot.x = ft_deg_to_rad(cone->rot.x);
	cone->rot.y = ft_deg_to_rad(cone->rot.y);
	cone->rot.z = ft_deg_to_rad(cone->rot.z);
	cone->origin = trans(cone->origin, cone->tran);
	cone->axis = rotate(cone->axis, cone->rot);
	vector_normalize(&cone->axis);
	r->is_okey[2] = '1';
}

void		set_cone(char **words, t_rtv1 *r)
{
	t_shape		*shape;
	t_cone		*cone;
	t_shape		*elt;

	shape = (t_shape*)ft_memalloc(sizeof(t_shape));
	cone = (t_cone*)ft_memalloc(sizeof(t_cone));
	cone->origin = get_vect_from_str(words[1]);
	cone->radius = ft_atof(words[2]);
	cone->height = ft_atof(words[3]);
	cone->color = get_color_from_str(words[4]);
	cone->axis = get_vect_from_str(words[5]);
	add_rot_tran(r, cone, words[6], words[7]);
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
