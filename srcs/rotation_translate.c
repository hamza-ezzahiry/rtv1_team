/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_translate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:00:29 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/26 17:03:55 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	This is the translation function
*/

t_vect		trans(t_vect v, t_vect t)
{
	t_vect	res;

	res.x = v.x + t.x;
	res.y = v.y + t.y;
	res.z = v.z + t.z;
	return (res);
}

/*
**	This is the rotation function, j ai appliqué ça :
**  https://github.com/VBrazhnik/FdF/wiki/How-to-rotate-figure-in-3D%3F
*/

t_vect		rotate(t_vect v, t_vect r)
{
	t_vect res;

	res.x = v.x;
	res.y = v.y * cos(r.x) + v.z * sin(r.x);
	res.z = -v.y * sin(r.x) + v.z * cos(r.x);
	v = (t_vect) {res.x, res.y, res.z};
	res.x = v.x * cos(r.y) + v.z * sin(r.y);
	res.y = v.y;
	res.z = -v.x * sin(r.y) + v.z * cos(r.y);
	v = (t_vect) {res.x, res.y, res.z};
	res.x = v.x * cos(r.z) - v.y * sin(r.z);
	res.y = v.x * sin(r.z) + v.y * cos(r.z);
	res.z = v.z;
	return (res);
}
