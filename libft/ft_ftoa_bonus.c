/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:07:39 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/05 02:47:50 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int			intlen(long double n)
{
	int	ret;

	ret = 0;
	if (n < 0)
	{
		n = -n;
		ret++;
	}
	if (n < 1)
		ret++;
	while (n >= 1)
	{
		ret++;
		n /= 10;
	}
	return (ret);
}

static long long	ft_pow(int x, int y)
{
	long long	ret;

	ret = 1;
	while (y-- > 0)
		ret *= x;
	return (ret);
}

static void			fill_fraction(char *str, long double n, int precision)
{
	int		carry_flag;
	char	ch;

	n *= ft_pow(10, precision);
	carry_flag = (long long)n % 10 > 4;
	while (precision-- > 0)
	{
		ch = (long long)n % 10 + carry_flag + '0';
		if (ch > '9')
			ch = '0';
		else
			carry_flag = 0;
		if (ch < '0')
			ch = '0';
		*str = ch;
		str--;
		n /= 10;
	}
}

static void			fill_integer(char *str, long double n, int ilen)
{
	char	ch;

	while (ilen-- > 0)
	{
		ch = (long long)n % 10 + '0';
		if (ch < '0')
			ch = '0';
		str[ilen] = ch;
		n /= 10;
	}
}

char				*ft_ftoa(long double n, int precision)
{
	int			ilen;
	char		*ret;
	int			sign;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	ilen = intlen(n);
	ret = malloc(ilen + sign + precision + 2);
	if (!ret)
		return (NULL);
	ret[0] = '-';
	ret[ilen + sign + precision + 1] = '\0';
	if (precision > 0)
		ret[ilen + sign] = '.';
	else
		ret[ilen + sign] = '\0';
	fill_fraction(ret + ilen + sign + precision, n, precision);
	fill_integer(ret + sign, n, ilen);
	return (ret);
}
