/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:03:21 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/31 11:44:15 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			is_everything_okey(char *tab)
{
	int	i;

	i = -1;
	while (i++ < 3)
		if (tab[i] == '0')
			return (-1);
	return (1);
}

int			ft_open(char *filename)
{
	int fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_error(0);
	}
	return (fd);
}

void		checker(char *line, t_rtv1 *r)
{
	char	**words;
	int		nb_word;

	words = ft_strsplit(line, ' ');
	nb_word = count(words);
	if (!ft_strcmp(words[0], "camera") && nb_word == 4)
		set_camera(words, r);
	else if (!ft_strcmp(words[0], "light") && nb_word == 4)
		set_light(words, r);
	else if (!ft_strcmp(words[0], "sphere") && nb_word == 6)
		set_sphere(words, r);
	else if (!ft_strcmp(words[0], "plane") && nb_word == 6)
		set_plane(words, r);
	else if (!ft_strcmp(words[0], "cylindre") && nb_word == 8)
		set_cylindre(words, r);
	else if (!ft_strcmp(words[0], "cone") && nb_word == 8)
		set_cone(words, r);
	else
	{
		make_free(words);
		ft_error(3);
	}
	make_free(words);
}

void	fill_in(char *s)
{
	s[0] = '0';
	s[1] = '0';
	s[2] = '0';
}

int			parse(t_rtv1 *r, char *s)
{
	char	*line;

	r->fd = ft_open(s);
	fill_in(r->is_okey);
	if (get_next_line(r->fd, &line) == 1 && line != NULL && ft_strlen(line))
		checker(line, r);
	else
	{
		free(line);
		ft_error(0);
	}
	free(line);
	while (get_next_line(r->fd, &line) > 0)
	{
		if (ft_strlen(line))
			checker(line, r);
		free(line);
	}
	return (is_everything_okey(r->is_okey));
}
