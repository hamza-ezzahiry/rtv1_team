/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_cal2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 14:56:59 by hezzahir          #+#    #+#             */
/*   Updated: 2020/02/02 11:40:20 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		vector_scalar(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		distance(t_vect v1, t_vect v2)
{
	return ((v1.x - v2.x) * (v1.x - v2.x) +
			(v1.y - v2.y) * (v1.y - v2.y) +
			(v1.z - v2.z) * (v1.z - v2.z));
}

double		vector_snorme(t_vect v1)
{
	return (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

void		vector_normalize(t_vect *v1)
{
	double norme;

	norme = sqrt(vector_snorme(*v1));
	v1->x /= norme;
	v1->y /= norme;
	v1->z /= norme;
}

t_vect		vector_cross(t_vect u, t_vect v)
{
	t_vect vec;

	vec.x = u.y * v.z - u.z * v.y;
	vec.y = u.z * v.x - u.x * v.z;
	vec.z = u.x * v.y - u.y * v.x;
	return (vec);
}
