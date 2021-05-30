/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:16:08 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/30 17:37:47 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double ret;
	int sign;
	double decimal;

	ret = ft_atoi(str);
	sign = 1;
	if (ret < 0)
	{
		sign = -1;
		ret *= -1;
	}
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
