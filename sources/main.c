/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 15:24:18 by kzina             #+#    #+#             */
/*   Updated: 2019/08/09 03:14:30 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include "mlx.h"

int		main(int ac, char **av)
{
	t_mlx	*t;
	char	*str;
	t_cord	**map;

	if (ac != 2)
	{
		ft_putstr("usage: fdf input_file\n");
		return (1);
	}
	if ((str = reader(open(av[1], O_RDONLY))) == NULL)
	{
		ft_putstr("reading from file error\n");
		return (1);
	}
	if (check(str) == 1)
		return (error_messege(1));
	t = init_map();
	map = pars(str, t);
	t->cord = map;
	find_mid(t->cord, t);
	controls(t);
	render(map, t);
	mlx_loop(t->mlx);
	return (0);
}
