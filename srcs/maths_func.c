/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 00:57:25 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/26 17:13:09 by hezzahir         ###   ########.fr       */
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
