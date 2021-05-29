/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 22:57:41 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/29 23:17:40 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	clamp(int x, int min, int max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

int	rgb_to_int(t_color rgb)
{
	int	r;
	int g;
	int b;

	r = clamp(rgb.r, 0, 255);
	g = clamp(rgb.g, 0, 255);
	b = clamp(rgb.b, 0, 255);
	return (r << 16 | g << 8 | b);
}
