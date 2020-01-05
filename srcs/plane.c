/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 21:54:26 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/05 11:52:10 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

void		set_plane(char **words, t_rtv1  *r)
{
	t_shape		*new_sh;
	t_sphere	*sp;

	new_sh = (t_shape*)malloc(sizeof(t_shape));
	sp = (t_sphere*)malloc(sizeof(t_sphere));

	sp->origin = get_vect_from_str(words[1]);
	sp->radius = atof(words[2]);
	sp->color = get_color_from_str(words[3]);
}
