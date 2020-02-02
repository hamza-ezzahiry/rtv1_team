/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 15:16:44 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/31 20:23:39 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


/*
**	This file only for testing every functions (we call that unit-test)
*/

int		is_double(char *word)
{
	int	i;
	int	nb_point;

	i = 0;
	nb_point = 0;
	if (word[i] == '-' || word[i] == '+')
		i++;
	if (!ft_isdigit(word[i]))
		return (0);
	while (word[i])
	{
		if (ft_isdigit(word[i]) || word[i] == '.')
		{
			if (word[i] == '.')
				nb_point++;
		}
		else
			return (0);
		i++;
	}
	if (word[i - 1] == '.' || nb_point > 1)
		return (0);
	return (1);
}

int		is_fov(char *word)
{
	int	i;
	int	res;

	i = 0;
	if (ft_strlen(word) > 3)
		return (60);
	while (word[i])
	{
		if (!ft_isdigit(word[i]))
			return (60);
		i++;
	}
	res = ft_atoi(word);
	if (res > 180 || res <= 0)
		return (60);
	return (res);
}

int		is_int(char *word)
{
	int	i;

	i = 0;
	if (word[i] == '-' || word[i] == '+')
		i++;
	while (word[i])
	{
		if (!ft_isdigit(word[i]))
			return (0);
		i++;
	}
	return (1);
}

int		is_color(char *word)
{
	int	i;

	i = 0;
	if (ft_strlen(word) > 3)
		return (0);
	while (word[i])
	{
		if (!ft_isdigit(word[i]))
			return (0);
		i++;
	}
	if(ft_atoi(word) > 255)
		return (0);
	return (1);
}

int		main(void)
{
	char s[100] = "dkljkdsjk ldsjdlkkds ;kdlk;dks;d kdkdk llld lllld";
	char **words;

	words = ft_strsplit(s, ' ');
	int i = 0;
	while(words[i] != 0)
	{
		printf("%s\n", words[i]);
		i++;
	}
	printf("| %d |", i);
	return (0);
}
