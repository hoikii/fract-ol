/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 22:57:41 by kanlee            #+#    #+#             */
/*   Updated: 2021/07/09 18:44:35 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "utils.h"

int	rgb_to_int(t_color rgb)
{
	int	r;
	int	g;
	int	b;

	r = clamp_i(rgb.r, 0, 255);
	g = clamp_i(rgb.g, 0, 255);
	b = clamp_i(rgb.b, 0, 255);
	return (r << 16 | g << 8 | b);
}

t_color	get_palette(int i)
{
	t_color	palette[16];

	palette[0] = (t_color){66, 30, 15};
	palette[1] = (t_color){25, 7, 26};
	palette[2] = (t_color){9, 1, 47};
	palette[3] = (t_color){4, 4, 73};
	palette[4] = (t_color){0, 7, 100};
	palette[5] = (t_color){12, 44, 138};
	palette[6] = (t_color){24, 82, 177};
	palette[7] = (t_color){57, 125, 209};
	palette[8] = (t_color){134, 181, 229};
	palette[9] = (t_color){211, 236, 248};
	palette[10] = (t_color){241, 233, 191};
	palette[11] = (t_color){248, 201, 95};
	palette[12] = (t_color){255, 170, 0};
	palette[13] = (t_color){204, 128, 0};
	palette[14] = (t_color){153, 87, 0};
	palette[15] = (t_color){106, 52, 3};
	return (palette[i]);
}
