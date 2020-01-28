/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 22:24:41 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/28 22:37:56 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	light <position> <intensity> <color>
*/

void		set_light(char **words, t_rtv1 *r)
{
	t_light	*light;
	t_light *elt;

	light = (t_light*)ft_memalloc(sizeof(t_light));
	light->origin = get_vect_from_str(words[1]);
	light->intensity = ft_atof(words[2]);
	light->color = get_color_from_str(words[3]);
	light->next = NULL;
	elt = r->light;
	if (r->light == NULL)
		r->light = light;
	else
	{
		while (elt->next != NULL)
			elt = elt->next;
		elt->next = light;
	}
}
