/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 18:37:08 by hezzahir          #+#    #+#             */
/*   Updated: 2020/02/02 11:34:30 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			count(char **words)
{
	int	nb;

	nb = 0;
	if (!words)
		return (0);
	while (words[nb] != 0)
		nb++;
	return (nb);
}

void		ft_error(int id)
{
	if (id == 0)
		perror("rtv1");
	else if (id == 1)
		ft_putendl("Error: vector not valid");
	else if (id == 2)
		ft_putendl("Error: color not valid");
	else if (id == 3)
		ft_putendl("Error: No data found");
	exit(0);
}

void		make_free(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		ft_memdel((void **)&words[i]);
		i++;
	}
	ft_memdel((void **)&words);
}

t_vect		get_vect_from_str(char *str)
{
	t_vect	v;
	char	**mots;

	mots = ft_strsplit(str, ',');
	v = (t_vect) {0, 0, 0};
	if (count(mots) == 3)
	{
		if (is_double(mots[0]) && is_double(mots[1]) && is_double(mots[0]))
		{
			v.x = ft_atof(mots[0]);
			v.y = ft_atof(mots[1]);
			v.z = ft_atof(mots[2]);
		}
		else
		{
			make_free(mots);
			ft_error(1);
		}
	}
	else
		ft_error(1);
	make_free(mots);
	return (v);
}

t_color		get_color_from_str(char *str)
{
	char	**mots;
	t_color	c;

	mots = ft_strsplit(str, ',');
	c = (t_color) {0, 0, 255};
	if (count(mots) == 3)
	{
		if (is_color(mots[0]) && is_color(mots[1]) && is_color(mots[0]))
		{
			c.r = ft_atoi(mots[0]);
			c.g = ft_atoi(mots[1]);
			c.b = ft_atoi(mots[2]);
		}
		else
		{
			make_free(mots);
			ft_error(2);
		}
	}
	else
		ft_error(2);
	make_free(mots);
	return (c);
}
