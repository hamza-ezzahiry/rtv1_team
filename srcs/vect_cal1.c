/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_cal1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 17:15:38 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/01/12 14:58:06 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	vector_generate(t_vect *v1, double x, double y, double z)
{
	v1->x = x;
	v1->y = y;
	v1->z = z;
}

t_vect	vector_sum(t_vect v1, t_vect v2)
{
	t_vect res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vect	vector_sub(t_vect v1, t_vect v2)
{
	t_vect res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vect	vector_multi(t_vect v1, double a)
{
	t_vect res;

	res.x = v1.x * a;
	res.y = v1.y * a;
	res.z = v1.z * a;
	return (res);
}

t_vect	vector_div(t_vect v1, double a)
{
	t_vect res;

	res.x = v1.x / a;
	res.y = v1.y / a;
	res.z = v1.z / a;
	return (res);
}
