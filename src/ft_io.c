/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:47:44 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/24 10:05:25 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

static void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	*ft_realloc(void *ptr, size_t size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		while (size-- > 0)
			((char *)new_ptr)[size] = ((char *)ptr)[size];
		free(ptr);
	}
	return (new_ptr);
}

static void	ft_read_line(int line, char **split, t_points *points)
{
	int		i;
	int		count;

	count = 0;
	while (split[count])
		count++;
	points->array = ft_realloc(points->array, sizeof(t_point3) * points->size, \
		sizeof(t_point3) * (points->size + count));
	points->size += count;
	i = 0;
	while (split[i])
	{
		points->array[i + line * points->width].x = i;
		points->array[i + line * points->width].y = line;
		if (split[i][0] == '0' && split[i][1] == 'X')
			points->array[i + line * points->width].z
				= ft_atoi_base(split[i] + 2, "0123456789ABCDEF");
		else if (split[i][0] == '0' && split[i][1] == 'x')
			points->array[i + line * points->width].z
				= ft_atoi_base(split[i] + 2, "0123456789abcdef");
		else
			points->array[i + line * points->width].z = ft_atoi(split[i]);
		i++;
	}
	points->width = i;
}

void	ft_read_file(const char *file_name, t_points *points)
{
	int			fd;
	char		*line;
	char		**split;
	int			i;

	fd = open(file_name, O_RDONLY);
	points->size = 0;
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	points->array = malloc(sizeof(t_point3) * points->size);
	if (!points->array)
		return ;
	i = 0;
	while (line)
	{
		split = ft_split(line, ' ');
		ft_read_line(i, split, points);
		ft_free_split(split);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}
