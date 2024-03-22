/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:36:40 by fltorren          #+#    #+#             */
/*   Updated: 2024/03/22 13:37:54 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	close_hook(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_data *data)
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

int	mouse_hook(int button, int x, int y, t_data *data)
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
