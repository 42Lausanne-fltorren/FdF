/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:06:02 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/01 11:36:13 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

static int	close_hook(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

static int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
		return (close_hook(data));
	if (keycode == NUM_PLUS)
		data->alpha += 0.1;
	if (keycode == NUM_MINUS)
		data->alpha -= 0.1;
	if (keycode == UP)
		data->y0 -= 10;
	if (keycode == DOWN)
		data->y0 += 10;
	if (keycode == LEFT)
		data->x0 -= 10;
	if (keycode == RIGHT)
		data->x0 += 10;
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	ft_render_points(data->points, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

static int	mouse_hook(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 4)
		data->zoom += 0.5;
	if (button == 5)
		data->zoom -= 0.5;
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	ft_render_points(data->points, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_points	points;
	t_data		data;

	if (argc != 2)
		return (0);
	ft_read_file(argv[1], &points);
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
