/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:40:57 by kzina             #+#    #+#             */
/*   Updated: 2019/08/09 17:55:03 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include "mlx.h"

void	cord_del(t_cord **map, t_mlx *param)
{
	int		x;

	x = 0;
	while (x < param->coloms * param->lines)
	{
		free(map[x]);
		x++;
	}
}

void	mlx_del(t_mlx *param)
{
	if (param->win != NULL)
		mlx_destroy_window(param->mlx, param->win);
	if (param->img != NULL)
	{
		if (param->img->image != NULL)
			mlx_destroy_image(param->mlx, param->img->image);
		ft_memdel((void **)param->img);
	}
	if (param->menu != NULL)
	{
		if (param->menu->image != NULL)
			mlx_destroy_image(param->mlx, param->menu->image);
		ft_memdel((void **)param->menu);
	}
	if (param->cord != NULL)
		ft_strarraydel((void ***)param->cord);
	ft_memdel((void **)&param);
}

void	clear_img(t_mlx *win)
{
	ft_bzero(win->img->data_address, WIDTH * HEIGH * 4);
	mlx_put_image_to_window(win->mlx, win->win, win->img->image, 0, 0);
}

t_mlx	*init_map(void)
{
	t_mlx	*ses;

	if ((ses = (t_mlx *)ft_memalloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	ses->mlx = mlx_init();
	ses->win = mlx_new_window(ses->mlx, WIDTH, HEIGH, "FDF");
	init_image(ses);
	ses->dx = 0;
	ses->dy = 0;
	ses->dz = 1;
	ses->y = -0.9;
	ses->x = 0.5;
	ses->color1 = 0xFF1493;
	ses->color2 = 0x00BFff;
	ses->color3 = 0xFF4500;
	return (ses);
}

void	init_image(t_mlx *ses)
{
	t_image	*img;
	t_image	*menu;
	int		width;
	int		height;

	width = 200;
	height = 1300;
	if ((img = (t_image *)ft_memalloc(sizeof(t_image))) == NULL)
		return ;
	if ((img->image = mlx_new_image(ses->mlx, WIDTH, HEIGH)) == NULL)
		return ;
	if ((menu = (t_image *)ft_memalloc(sizeof(t_image))) == NULL)
		return ;
	if ((menu->image = mlx_xpm_file_to_image(ses->mlx,
	"menu/menu.xpm", &width, &height)) == NULL)
		return ;
	img->data_address = (int *)mlx_get_data_addr(img->image,
	&img->bpp, &img->line_size, &img->endian);
	img->line_size /= 4;
	ses->menu = menu;
	ses->img = img;
}
