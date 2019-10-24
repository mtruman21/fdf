/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:02:56 by kzina             #+#    #+#             */
/*   Updated: 2019/08/09 03:19:19 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include "mlx.h"

int		get_color_map(t_cord *map, t_mlx *param)
{
	if (map->z > param->mid && map->color == 0xFFFFF1)
		return (param->color1);
	if (map->z < param->mid && map->color == 0xFFFFF1)
		return (param->color2);
	if (map->z == param->mid && map->color == 0xFFFFF1)
		return (param->color3);
	return (map->color);
}

void	find_mid(t_cord **map, t_mlx *param)
{
	int x;
	int min;
	int max;

	x = 0;
	max = 0;
	min = 0;
	while (x < param->lines * param->coloms)
	{
		if (map[x]->z > max)
			max = map[x]->z;
		if (map[x]->z < min)
			min = map[x]->z;
		x++;
	}
	param->mid = max - min;
}

void	swap_coor(int *x, int *y)
{
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

char	*reader(int fd)
{
	char	*input;
	char	*temp;
	char	*to_free;
	int		ct_str;

	ct_str = 0;
	input = (char*)ft_memalloc(sizeof(char));
	while (get_next_line(fd, &temp) > 0)
	{
		to_free = input;
		input = ft_strjoin(input, temp);
		ft_strdel((void **)&to_free);
		to_free = input;
		input = ft_strjoin(input, "\n");
		ft_strdel((void **)&to_free);
		ft_strdel((void **)&temp);
		ct_str++;
	}
	if (ct_str == 0)
		return (NULL);
	return (input);
}
