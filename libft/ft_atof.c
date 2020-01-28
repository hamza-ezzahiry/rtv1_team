/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:20:08 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/28 17:51:36 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double	ft_sign(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

double	ft_atof(const char *str)
{
	double	res;
	int		e;
	double	sign;
	char	*s;

	s = (char*)str;
	res = 0;
	e = 0;
	while (*s == '\t' || *s == ' ' || *s == '\n')
		s++;
	sign = ft_sign(*s);
	if (*s == '+' || *s == '-')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + *s - 48;
		s++;
	}
	if (*s == '.')
		while (*s++ != '\0' && ft_isdigit(*s))
		{
			res = res * 10.0 + (*s - '0');
			e--;
		}
	return ((res * pow(10.0, e)) * sign);
}
