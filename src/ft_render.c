/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:59:14 by fltorren          #+#    #+#             */
/*   Updated: 2023/12/15 11:31:19 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	ft_set(int x, int y, t_data *d, int color)
{
	int		i;
	int		bpp;
	int		size_line;
	int		endian;
	char	*data;

	data = mlx_get_data_addr(d->img, &bpp, &size_line, &endian);
	i = (x * 4) + (y * size_line);
	if (endian == 1)
	{
		data[i] = color >> 24;
		data[++i] = (color >> 16) & 0xFF;
		data[++i] = (color >> 8) & 0xFF;
		data[++i] = color & 0xFF;
	}
	else
	{
		data[i] = color & 0xFF;
		data[++i] = (color >> 8) & 0xFF;
		data[++i] = (color >> 16) & 0xFF;
		data[++i] = color >> 24;
	}
}

int	ft_map(int x, t_point3 p1, t_point3 p2, int range)
{
	return ((p2.z + x * (p1.z - p2.z) / range) * -1000);
}

void	ft_line(const t_point3 point1, const t_point3 point2, t_data *data)
{
	float		t;
	t_point3	l;
	t_point2	p;

	t = 0;
	while (t <= 1)
	{
		l.x = (float) point1.x + (float)(point2.x - point1.x)*t;
		l.y = (float) point1.y + (float)(point2.y - point1.y)*t;
		l.z = (float) point1.z + (float)(point2.z - point1.z)*t;
		p = ft_point(l, *data);
		if (p.x >= 0 && p.x <= data->width && p.y >= 0 && p.y <= data->height)
			ft_set(p.x, p.y, data, 0xFFFFFF - l.z * 500);
		t += 0.01;
	}
}

/**
	Projects the 3d point into 2d coordinates
**/
t_point2	ft_point(t_point3 p, t_data data)
{
	float		a;
	float		b;
	float		c;
	t_point2	point;

	a = data.zoom / sqrt(2);
	b = data.zoom * sin(data.alpha) / sqrt(2);
	c = data.zoom * cos(data.alpha);
	point.x = (int)(data.x0 + a * (p.x - p.y));
	point.y = (int)(data.y0 - c * (p.z) - b * (p.x + p.y));
	return (point);
}

void	ft_render_points(t_points points, t_data *data)
{
	int			i;
	t_point3	p;

	i = 0;
	while (i < points.size)
	{
		p = points.array[i];
		if (i % points.width != points.width - 1 && i + 1 < points.size)
			ft_line(p, points.array[i + 1], data);
		if (i + points.width < points.size)
			ft_line(points.array[i + points.width], p, data);
		i++;
	}
}
