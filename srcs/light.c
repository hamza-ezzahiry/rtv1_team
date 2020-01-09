/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 22:24:41 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/09 01:25:33 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	light <position> <intensity> <color>
*/

void		set_light(char **words, t_rtv1 *r)
{
	r->light.origin = get_vect_from_str(words[1]);
	r->light.intensity = atof(words[2]);
	r->light.color = get_color_from_str(words[3]);
}
