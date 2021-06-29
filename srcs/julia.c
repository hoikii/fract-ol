/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 16:40:57 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/29 14:13:50 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"
#include "color.h"

int		is_julia(t_complex z, int it_max, t_complex c)
{
	int			it;

	it = -1;
	while (++it < it_max)
	{
		z = c_add(c_square(z), c);
		if (c_abs_squared(z) >= 4.0)
			return (it);
	}
	return (0);
}

void	julia_calc(int screen_x, int screen_y, t_mlx *frame)
{
	t_complex vp;
	char *imgdata;
	t_color rgb;
	int pos;
	int it;

	vp.real = frame->upperleft.x + screen_x / frame->scale;
	vp.imag = frame->upperleft.y - screen_y / frame->scale;
	it = is_julia(vp, frame->it_max, frame->julia_constant);
	frame->iterations_per_pixel[screen_y][screen_x] = it;
	return ;
	if (it)
	{

		double quotient = (double)it / frame->it_max;
		int g = clamp(quotient * 255, 0, 255);
		rgb = (t_color){0, 1, 0};
		rgb.g = clamp(quotient * 255, 0, 255);
//		if (quotient > 0.5)
//			rgb = (t_color){g, 255, g};
//		else
//			rgb = (t_color){0, g, 0};

		put_pxl_to_image(screen_x, screen_y, frame, rgb);
	}
	else
		put_pxl_to_image(screen_x, screen_y, frame, (t_color){0, 0, 0});

}

