/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:35:52 by kzina             #+#    #+#             */
/*   Updated: 2019/08/09 01:39:14 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include "math.h"
#include "mlx.h"

double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		get_color(int start, int end, int current, t_linecor *col)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (col->color0 == col->color1)
		return (col->color1);
	percentage = percent(start, end, current);
	red = get_light((col->color0 >> 16) & 0xFF,
	(col->color1 >> 16) & 0xFF, percentage);
	green = get_light((col->color0 >> 8) & 0xFF,
	(col->color1 >> 8) & 0xFF, percentage);
	blue = get_light(col->color0 & 0xFF, col->color1 & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void	draw_line(t_line *line, int x1, t_mlx *params, t_linecor *xy)
{
	int		x;
	int		start;
	int		y;
	int		k;
	t_image	*param;

	param = params->img;
	x = line->x - 1;
	y = line->y;
	k = line->k;
	start = x + 1;
	while (x++ <= x1)
	{
		if (!(x >= WIDTH || x <= 0 || y >= HEIGH || y <= 0))
			if (param->data_address[(k == 1 ? y : x) *
			param->line_size + (k == 1 ? x : y)] == 0)
				param->data_address[(k == 1 ? y : x) *
			param->line_size + (k == 1 ? x : y)] = get_color(start, x1, x, xy);
		line->error -= line->dy;
		if (line->error < 0)
		{
			y += line->ystep;
			line->error += line->dx;
		}
	}
}

void	draw(t_linecor *xy, t_mlx *param)
{
	t_line	*line;

	line = (t_line *)ft_memalloc(sizeof(t_line));
	line->k = labs(xy->y1 - xy->y0) > labs(xy->x1 - xy->x0) ? 1 : 0;
	if (line->k)
	{
		swap_coor(&xy->x0, &xy->y0);
		swap_coor(&xy->x1, &xy->y1);
	}
	if (xy->x0 > xy->x1)
	{
		swap_coor(&xy->x0, &xy->x1);
		swap_coor(&xy->y0, &xy->y1);
	}
	line->dx = xy->x1 - xy->x0;
	line->dy = labs(xy->y1 - xy->y0);
	line->error = line->dx / 2;
	line->ystep = xy->y0 < xy->y1 ? 1 : -1;
	line->y = xy->y0;
	line->x = xy->x0;
	draw_line(line, xy->x1, param, xy);
	ft_strdel((void **)&line);
}
