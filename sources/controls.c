/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:10:19 by kzina             #+#    #+#             */
/*   Updated: 2019/08/09 04:10:52 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include "mlx.h"

void	xy_rotate(int keycode, t_mlx *param)
{
	if (keycode == 91)
		param->y += 0.05;
	if (keycode == 84)
		param->y -= 0.05;
	if (keycode == 86)
		param->x -= 0.05;
	if (keycode == 88)
		param->x += 0.05;
}

void	offset(int keycode, t_mlx *param)
{
	if (keycode == 125)
		param->dx -= 10;
	if (keycode == 126)
		param->dx += 10;
	if (keycode == 123)
		param->dy += 10;
	if (keycode == 124)
		param->dy -= 10;
}

void	project(int keycode, t_mlx *param)
{
	if (keycode == 49)
	{
		if (param->x == 0 && param->y == 0)
		{
			param->x = 0.5;
			param->y = -0.9;
		}
		else
		{
			param->x = 0;
			param->y = 0;
		}
	}
}

int		key_press(int keycode, t_mlx *param)
{
	if (keycode == 53)
	{
		exit(0);
		mlx_del(param);
	}
	if (keycode == 91 || keycode == 88 || keycode == 84 || keycode == 86)
		xy_rotate(keycode, param);
	if (keycode == 125 || keycode == 126 || keycode == 123 || keycode == 124)
		offset(keycode, param);
	if (keycode == 49)
		project(keycode, param);
	if (keycode == 69)
		param->fact += 1;
	if (keycode == 78 && param->fact != 0)
		param->fact -= 1;
	if (keycode == 36)
		change_color(param);
	if (keycode == 258)
		dancing(param);
	if (keycode == 75 || keycode == 67)
		inc_z(keycode, param);
	render(param->cord, param);
	return (0);
}

void	controls(t_mlx *param)
{
	mlx_hook(param->win, 2, 0, key_press, param);
	mlx_hook(param->win, 17, 0, close, param);
}
