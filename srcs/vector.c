/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 17:15:38 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/01/03 18:37:47 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void vector_generate(t_vect *v1, double x, double y, double z)
{
    v1->x = x;
    v1->y = y;
    v1->z = z;
}

t_vect vector_sum(t_vect v1, t_vect v2)
{
    t_vect res;

    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    return (res);
}

t_vect vector_sub(t_vect v1, t_vect v2)
{
    t_vect res;

    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    res.z = v1.z - v2.z;
    return (res);
}

t_vect vector_multi(t_vect v1, double a)
{
    t_vect res;

    res.x = v1.x * a;
    res.y = v1.y * a;
    res.z = v1.z * a;
    return (res);
}

t_vect vector_div(t_vect v1, double a)
{
    t_vect res;

    res.x = v1.x / a;
    res.y = v1.y / a;
    res.z = v1.z / a;
    return (res);
}

double vector_scalar(t_vect v1, t_vect v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double vector_snorme(t_vect v1)
{
    return (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

void vector_normalize(t_vect *v1)
{
    double norme;

    norme = sqrt(vector_snorme(*v1));
    v1->x /= norme;
    v1->y /= norme;
    v1->z /= norme;
}
