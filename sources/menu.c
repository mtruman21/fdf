/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 22:12:42 by kzina             #+#    #+#             */
/*   Updated: 2019/08/09 04:09:40 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include "mlx.h"

void	put_image(t_mlx *param)
{
	mlx_put_image_to_window(param->mlx, param->win, param->img->image, 0, 0);
	mlx_put_image_to_window(param->mlx, param->win,
	param->menu->image, -50, -60);
}

int		error_messege(int i)
{
	ft_putstr("file error");
	return (i);
}

void	change_color(t_mlx *param)
{
	if (param->color1 == 0xFF1493)
	{
		param->color1 = 0xF5D6C6;
		param->color2 = 0x6B5B95;
		param->color3 = 0xFFFFFF;
	}
	else
	{
		param->color1 = 0xFF1493;
		param->color2 = 0x00BFff;
		param->color3 = 0xFF4500;
	}
}

void	dancing(t_mlx *param)
{
	param->color1 -= 100;
	param->color2 -= 100;
	param->color3 -= 100;
}

void	inc_z(int keycode, t_mlx *param)
{
	if (keycode == 75)
		param->dz += 1;
	if (keycode == 67)
		param->dz -= 1;
}
