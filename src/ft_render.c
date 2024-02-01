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
	t_point2	point;

	point.x = (sqrt(2.0f) / 2.0f * (p.x - p.y)) * data.zoom + data.x0;
	point.y = (sqrt(2.0f / 3.0f) * (-p.z) - 1.0f / sqrt(6.0f) * (p.x + p.y)) * data.zoom + data.y0;
	return (point);
}

void	ft_render_points(t_points points, t_data *data)
{
	int			w;
	int			h;
	t_point3	p;

	h = 0;
	while (h < points.size / points.width)
	{
		w = 0;
		while (w < points.width)
		{
			p = points.array[w + h * points.width];
			if (h > 0)
				ft_line(points.array[w + (h - 1) * points.width], p, data);
			if (w > 0)
				ft_line(points.array[w - 1 + h * points.width], p, data);
			w++;
		}
		h++;
	}
}
