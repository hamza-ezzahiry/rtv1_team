/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 18:37:08 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/05 12:56:51 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		count(const char *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			count += 1;
		if (s[i] != c && s[i + 1] == '\0')
			count += 1;
		i++;
	}
	return (count);
}

t_vect	get_vect_from_str(char *str)
{
	char	**mots;
	t_vect	v;

	if(count(str, ',') == 3)
	{
		mots = ft_strsplit(str, ',');
		if(is_double(mots[0]) && is_double(mots[1]) && is_double(mots[0]))
		{
			v.x = atof(mots[0]);
			v.y = atof(mots[1]);
			v.z = atof(mots[2]);
		}
		else
		{
			make_free(mots);
			ft_putendl("Error: vector not valid");
			exit(0);
		}
	}
	else
	{
		ft_putendl("Error: vector not valid");
		exit(0);
	}
	make_free(mots);
	return (v);
}

t_color		get_color_from_str(char *str)
{
	char	**mots;
	t_color	c;

	if(count(str, ',') == 3)
	{
		mots = ft_strsplit(str, ',');
		if(is_color(mots[0]) && is_color(mots[1]) && is_color(mots[0]))
		{
			c.r = ft_atoi(mots[0]);
			c.g = ft_atoi(mots[1]);
			c.b = ft_atoi(mots[2]);
		}
		else
		{
			make_free(mots);
			ft_putendl("Error: color not valid");
			exit(0);
		}
	}
	else
	{
		ft_putendl("Error: color not valid");
		exit(0);
	}
	make_free(mots);
	return (c);
}
