/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:48:18 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/24 09:58:32 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# define ESC 0x35
# define NUM_PLUS 0xffab
# define NUM_MINUS 0xffad
# define UP 0x7e
# define DOWN 0x7d
# define LEFT 0x7b
# define RIGHT 0x7c

typedef struct s_point3
{
	float	x;
	float	y;
	float	z;
}		t_point3;

typedef struct s_point2
{
	int	x;
	int	y;
}		t_point2;

typedef struct s_points
{
	t_point3	*array;
	int			width;
	int			size;
}		t_points;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	int			width;
	int			height;
	float		zoom;
	float		alpha;
	t_points	points;
	int			x0;
	int			y0;
	int			color_min;
	int			color_max;
}		t_data;

void		ft_read_file(const char *file_name, t_points *points);

void		ft_line(const t_point3 point1, const t_point3 point2, t_data *data);
void		ft_render_points(t_points points, t_data *data);
t_point2	ft_point(t_point3 p, t_data data);

int			ft_max(int a, int b);
int			ft_abs(int a);
int			ft_min(int a, int b);
int			ft_atoi_base(char *str, char *base);
#endif
