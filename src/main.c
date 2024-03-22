/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:06:02 by fltorren          #+#    #+#             */
/*   Updated: 2024/03/22 13:36:31 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

static int	ft_usage_error(void)
{
	write(2, "Usage: ./fdf [map]\n", 20);
	return (0);
}

static int	ft_map_error(void)
{
	write(2, "Error: Invalid map\n", 20);
	return (0);
}

int	main(int argc, char **argv)
{
	t_points	points;
	t_data		data;

	if (argc != 2)
		return (ft_usage_error());
	ft_read_file(argv[1], &points);
	if (!points.array || !points.size)
		return (ft_map_error());
	data.mlx = mlx_init();
	data.width = 600;
	data.height = 600;
	data.alpha = -1.4472;
	data.zoom = 3;
	data.win = mlx_new_window(data.mlx, data.width, data.height, "FdF");
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	data.points = points;
	data.x0 = data.width / 2;
	data.y0 = data.height;
	ft_render_points(points, &data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 1L << 19, close_hook, &data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
