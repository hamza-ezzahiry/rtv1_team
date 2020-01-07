/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:03:21 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/06 00:15:57 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			is_everything_okey(char *tab)
{
	int	i;

	i = -1;
	while (i++ < 10)
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
	char **words;

	words = ft_strsplit(line, ' ');
	if (!ft_strcmp(words[0], "camera"))
		set_camera(words, r);
	else if (!ft_strcmp(words[0], "sphere"))
		set_sphere(words, r);
	/* else if (!ft_strcmp(words[0], "plane"))
		set_plane(words, r);
	else if (!ft_strcmp(words[0], "light"))
		set_light(words, r);
	else if (!ft_strcmp(words[0], "cylinder"))
		set_cylinder(words, r);
	make_free(words); */
	//print_error(r->is_okey);
}

int			parse(t_rtv1 *r, char *s)
{
	char	*line;

	//init_tab(r->is_okey);
	r->fd = ft_open(s);
	if (get_next_line(r->fd, &line) == 1 && line != NULL)
		checker(line, r);
	else
	{
		free(line);
		ft_error(0);
	}
	free(line);
	while (get_next_line(r->fd, &line) > 0)
	{
		checker(line, r);
		free(line);
	}
	return (1);
}
