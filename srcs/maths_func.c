/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 00:57:25 by hezzahir          #+#    #+#             */
/*   Updated: 2020/02/09 15:11:29 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_sqrs(double x)
{
	return (x * x);
}

double	ft_deg_to_rad(double angle)
{
	return ((angle / 180.0) * M_PI);
}

void	vect_init(t_ray *ray, t_intersection intersect, t_vect origin)
{
	ray->origin = vector_sum(intersect.p_inter,
			vector_div(intersect.normal, 1E10));
	ray->dir = vector_sub(origin, ray->origin);
	vector_normalize(&ray->dir);
}
