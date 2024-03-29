/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:16:08 by kanlee            #+#    #+#             */
/*   Updated: 2021/11/23 14:51:03 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chk_sign(const char *str)
{
	int	sign;

	sign = 1;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	return (sign);
}

double	ft_atof(const char *str)
{
	double	ret;
	int		sign;
	double	decimal;

	ret = ft_atoi(str);
	sign = chk_sign(str);
	if (ret < 0)
		ret *= -1;
	while (*str == '+' || *str == '-' || ft_isdigit(*str))
		str++;
	decimal = 1.0;
	if (*str == '.')
	{
		while (*(++str))
		{
			if (!ft_isdigit(*str))
				break ;
			ret = ret + (*str - '0') * (decimal /= 10);
		}
	}
	return (ret * sign);
}
