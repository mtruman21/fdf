/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:05:02 by kzina             #+#    #+#             */
/*   Updated: 2019/08/09 04:51:18 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include <string.h>
#include <stdio.h>

int		color(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(8);
	while (str[i] != ',' && str[i])
		i++;
	i = str[i] ? i + 3 : i;
	while (str[i] != '\0')
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	j = ft_atoi_base(tmp, 16);
	ft_strdel((void **)&tmp);
	return (j);
}

int		check_point(char *line)
{
	int i;

	i = 0;
	if (line[i] == '-')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i] == '\0')
		return (0xFFFFF1);
	if (line[i] == ',' && line[i + 1] == '0' && line[i + 2] == 'x')
		return (color(&line[i]));
	return (-1);
}

int		check(char *str)
{
	char	**line1;
	int		i;

	i = 0;
	line1 = ft_strsplit(str, '\n');
	while (i < ft_count_word(str, '\n'))
	{
		if (ft_count_word(line1[0], ' ') != ft_count_word(line1[i], ' '))
			return (1);
		i++;
	}
	ft_strarraydel((void ***)&line1);
	return (0);
}

int		put_cord(char **str, t_cord **cord, int i, int l)
{
	int j;

	j = 0;
	while (j < l)
	{
		if (check_point(str[j]) != -1)
		{
			cord[i] = (t_cord *)ft_memalloc(sizeof(t_cord));
			cord[i]->y = i / l;
			cord[i]->x = i - (cord[i]->y * l);
			cord[i]->z = ft_atoi(str[j]);
			cord[i]->color = check_point(str[j]);
			i++;
		}
		else
		{
			ft_strdel((void **)cord);
			return (0);
		}
		j++;
	}
	return (i);
}

t_cord	**pars(char *str, t_mlx *map)
{
	t_cord	**head;
	char	**line;
	char	**line2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = ft_strsplit(str, '\n');
	head = (t_cord **)ft_memalloc(sizeof(t_cord *) * ft_count_word(str, '\n')
	* ft_count_word(line[i], ' '));
	while (i < ft_count_word(str, '\n'))
	{
		line2 = ft_strsplit(line[i], ' ');
		j = put_cord(line2, head, j, ft_count_word(line[i], ' '));
		ft_strarraydel((void ***)&line2);
		i++;
	}
	map->lines = ft_count_word(str, '\n');
	map->coloms = ft_count_word(line[1], ' ');
	map->fact = WIDTH / ((map->coloms > map->lines
	? map->coloms : map->lines) * 2);
	ft_strdel((void **)&str);
	ft_strarraydel((void ***)&line);
	return (head);
}
