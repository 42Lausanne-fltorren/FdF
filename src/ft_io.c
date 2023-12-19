/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:47:44 by fltorren          #+#    #+#             */
/*   Updated: 2023/12/15 14:32:51 by fltorren         ###   ########.fr       */
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

static void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
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
	points->size += count;
	points->array = ft_realloc(points->array, sizeof(t_point3) * points->size);
	i = 0;
	while (split[i])
	{
		points->array[points->size - count + i].x = i;
		points->array[points->size - count + i].y = line;
		points->array[points->size - count + i].z = ft_atoi(split[i]);
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
