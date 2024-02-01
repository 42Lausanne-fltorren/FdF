/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:42:46 by fltorren          #+#    #+#             */
/*   Updated: 2024/01/10 01:00:05 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	ft_atoi_hex(char *str)
{
	int	i;
	int	n;

	i = 2;
	n = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9' && n < 6)
			n = n * 16 + str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F' && n < 6)
			n = n * 16 + str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f' && n < 6)
			n = n * 16 + str[i] - 'a' + 10;
		else
			return (n);
		i++;
	}
	return (n);
}
