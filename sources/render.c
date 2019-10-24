/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 16:40:34 by kzina             #+#    #+#             */
/*   Updated: 2019/08/09 05:07:53 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include "math.h"
#include "mlx.h"

void		factor_map(t_mlx *param, t_cord **map)
{
	int x;

	x = 0;
	while (x < param->lines * param->coloms)
	{
		map[x]->x *= param->fact;
		map[x]->y *= param->fact;
		map[x]->z *= param->fact;
		x++;
	}
}

t_linecor	*rotate(t_linecor *line, t_mlx *param)
{
	double	x;
	double	y;
	double	z;

	x = line->x0;
	z = line->z0;
	y = line->y0;
	line->x0 = cos(param->y) * x + sin(param->y) * z;
	line->z0 = -sin(param->y) * x + cos(param->y) * z;
	z = line->z0;
	line->y0 = cos(param->x) * y - sin(param->x) * z;
	line->z0 = sin(param->x) * y + cos(param->x) * z;
	x = line->x1;
	z = line->z1;
	y = line->y1;
	line->x1 = cos(param->y) * x + sin(param->y) * z;
	line->z1 = -sin(param->y) * x + cos(param->y) * z;
	z = line->z1;
	line->y1 = cos(param->x) * y - sin(param->x) * z;
	line->z1 = sin(param->x) * y + cos(param->x) * z;
	return (line);
}

void		write_cor(t_cord *map, t_cord *map2, t_mlx *param)
{
	t_linecor	*line;

	line = (t_linecor *)ft_memalloc(sizeof(t_linecor));
	line->x0 = map->y;
	line->y0 = map->x;
	line->x1 = map2->y;
	line->y1 = map2->x;
	line->z0 = map->z * param->dz;
	line->z1 = map2->z * param->dz;
	line->color0 = get_color_map(map, param);
	line->color1 = get_color_map(map2, param);
	line = rotate(line, param);
	line->x0 += WIDTH / 2 + param->dx;
	line->y0 += HEIGH / 2 + param->dy;
	line->x1 += WIDTH / 2 + param->dx;
	line->y1 += HEIGH / 2 + param->dy;
	draw(line, param);
	ft_strdel((void **)&line);
}

t_cord		**copy(t_cord **map, t_mlx *param)
{
	t_cord	**map2;
	int		x;

	x = 0;
	map2 = (t_cord **)ft_memalloc(sizeof(t_cord)
	* param->lines * param->coloms);
	while (x < param->coloms * param->lines)
	{
		map2[x] = (t_cord *)ft_memalloc(sizeof(t_cord));
		map2[x]->x = map[x]->x - param->coloms / 2;
		map2[x]->y = map[x]->y - param->lines / 2;
		map2[x]->z = map[x]->z;
		map2[x]->color = map[x]->color;
		x++;
	}
	return (map2);
}

void		render(t_cord **map, t_mlx *param)
{
	int		x;
	int		y;
	t_cord	**map2;

	y = 0;
	map2 = copy(map, param);
	factor_map(param, map2);
	clear_img(param);
	while (y < param->lines)
	{
		x = 0;
		while (x < param->coloms)
		{
			if (y > 0)
				write_cor(map2[x + (y * param->coloms)],
				map2[x + ((y - 1) * param->coloms)], param);
			if (x != param->coloms - 1)
				write_cor(map2[x + (y * param->coloms)],
				map2[x + 1 + (y * param->coloms)], param);
			x++;
		}
		y++;
	}
	put_image(param);
	ft_strarraydel((void ***)&map2);
}
