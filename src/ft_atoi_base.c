/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:42:31 by fltorren          #+#    #+#             */
/*   Updated: 2024/01/10 01:03:20 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

static unsigned int	ft_checkbase(char *base)
{
	unsigned int	len;
	unsigned int	j;

	len = 0;
	while (base[len])
	{
		if (base[len] == '+' || base[len] == '-')
			return (0);
		j = len;
		while (base[++j])
		{
			if (base[j] == base[len])
				return (0);
		}
		len++;
	}
	return (len);
}

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

static int	ft_baseindex(char c, char *base)
{
	unsigned int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

static unsigned int	ft_strtonbr(char *str, char *base, unsigned int blen)
{
	unsigned int	n;

	n = 0;
	while (*str && ft_baseindex(*str, base) >= 0)
	{
		n = blen * n + ft_baseindex(*str, base);
		str++;
	}
	return (n);
}

int	ft_atoi_base(char *str, char *base)
{
	int				sign;
	unsigned int	nbr;
	unsigned int	blen;

	blen = ft_checkbase(base);
	if (blen <= 1)
		return (0);
	while (*str && ft_isspace(*str))
		str++;
	sign = 1;
	while (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	nbr = ft_strtonbr(str, base, blen);
	return (sign * nbr);
}
/*#include <stdio.h>

int main()
{
	char *base = "0123456789";
	char *n = "  	 	\f\v\n\r\t 	 \n+-+--+-+-+++--2147483648-ffjn";
	printf("%d\n", ft_atoi_base(n, base));
}*/
